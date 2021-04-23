#include "../includes/cub3d.h"
#define  EPS            (1e-06)
#define  is_zero(d)     (fabs(d) < EPS)
#define  deg2rad(d)     ((d)*M_PI/180.0)    /* degree to radian */
#define  rad2deg(d)     ((d)*180.0/M_PI)    /* radian to degree */
#define  min(a,b)       ((a)<(b)? (a):(b))
#define  max(a,b)       ((a)>(b)? (a):(b))
#define  SX         800     /* screen width */
#define  SY         600     /* screen height */
#define  FOV        60      /* field of view (in degree) */
#define  FOV_H      deg2rad(FOV)
#define  FOV_V      (FOV_H*(double)SY/(double)SX)
#define  WALL_H     1.0
#define  MAPX   11
#define  MAPY   15
# define KEY_EVENT_PRESS    2
#define  ROT_UNIT   0.03    /* rad */
#define  MOVE_UNIT  0.1
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
#define  T2PI       6.28318530717958647692
static const double ANGLE_PER_PIXEL = FOV_H / (SX-1.);
static const double FOVH_2 = FOV_H / 2.0;
enum { VERT, HORIZ };
typedef enum 
{
    DIR_N=0,
    DIR_E,
    DIR_W,
    DIR_S
}       dir_t;
static int map[MAPX][MAPY] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };
///////////////////////////////

typedef struct    s_img
{
    void        *img;
    int            *data;
    int            bpp;
    int            line_size;
    int            endian;
}                t_img;
 
typedef struct    s_game
{
    void        *mlx;
    void        *win;
    int            map[MAPX][MAPY];
    t_img        img;
	double px;
	double py;
	double th;
}               t_game;

int map_get_cell( int x, int y )
{
    return (x >= 0 && x < MAPX && y >= 0 && y < MAPY) ? map[x][y] : -1;
}

int sgn( double d )
{
    return is_zero(d) ? 0 : ((d > 0) ? 1 : -1);
}

double l2dist( double x0, double y0, double x1, double y1 )
{
    double dx = x0 - x1;
    double dy = y0 - y1;
    return sqrt(dx*dx + dy*dy);
}

bool get_wall_intersection( double ray, double px, double py, dir_t* wdir, double* wx, double* wy )
{
    int xstep = sgn( cos(ray) );  /* +1 (right), 0 (no change), -1 (left) */
    int ystep = sgn( sin(ray) );  /* +1 (up),    0 (no change), -1 (down) */

    double xslope = (xstep == 0) ? INFINITY : tan(ray);
    double yslope = (ystep == 0) ? INFINITY : 1./tan(ray);

    double nx = (xstep > 0) ? floor(px)+1 : ((xstep < 0) ? ceil(px)-1 : px);
    double ny = (ystep > 0) ? floor(py)+1 : ((ystep < 0) ? ceil(py)-1 : py);

    //printf("\nray=%.2f deg, xstep=%d, ystep=%d, xslope=%.2f, yslope=%.2f, nx=%.2f, ny=%.2f\n", rad2deg(ray), xstep, ystep, xslope, yslope, nx, ny);

    double f=INFINITY, g=INFINITY;
    bool hit = false;
    int hit_side; /* either VERT or HORIZ */

    while( !hit )
    {
        int mapx, mapy;

        if( xstep != 0 ) f = xslope * (nx-px) + py;
        if( ystep != 0 ) g = yslope * (ny-py) + px;

        /* which is nearer to me - VERT(nx,f) or HORIZ(g,ny)? */
        double dist_v = l2dist(px, py, nx, f);
        double dist_h = l2dist(px, py, g, ny);

        if( dist_v < dist_h ) { /* VERT is nearer; go along x-axis */
            mapx = (xstep == 1) ? (int)(nx) : (int)(nx)-1 ;
            mapy = (int) f;
            hit_side = VERT;
           // printf(" V(%d, %.2f) ->", mapx, f);
        }
        else {  /* HORIZ is nearer; go along y-axis */
            mapx = (int) g;
            mapy = (ystep == 1) ? (int)(ny) : (int)(ny)-1 ;
            hit_side = HORIZ;
            //printf(" H(%.2f, %d) ->", g, mapy);
        }
        int cell = map_get_cell(mapx, mapy);
        if( cell < 0 ) break;   /* out of map */

        if( cell == 1 ) {   /* hit wall? */
            if( hit_side == VERT ) {
                *wdir = (xstep > 0) ? DIR_W : DIR_E;
                *wx = nx;
                *wy = f;
            }
            else { /* HORIZ */
                *wdir = (ystep > 0) ? DIR_S : DIR_N;
                *wx = g;
                *wy = ny;
            }
            hit = true;
           // printf(" hit wall!\n");
            break;
        }

        if( hit_side == VERT ) nx += xstep;
        else ny += ystep;
    }
    /* end of while(!hit) */

    return hit;
}

double cast_single_ray( int x, double px, double py, double th, dir_t* pdir)
{
    double ray = (th + FOVH_2) - (x * ANGLE_PER_PIXEL);
    double wx, wy;  /* coord. of wall intersection point */

    if( get_wall_intersection(ray, px, py, pdir, &wx, &wy) == false )
        return INFINITY; /* no intersection - maybe bad map? */

    double wdist = l2dist(px, py, wx, wy);
    wdist *= cos(th - ray);  /* 보정 */

    return wdist;
}



int get_wall_height( double dist )
{
    double fov_h = 2.0 * dist * tan(FOV_V/2.0);
    return (int)(SY * (WALL_H / fov_h)); /* in pixels */
}


void draw_wall(t_game *game, double wdist, int x, int color )
{
    int wh = get_wall_height(wdist);    /* wall height, in pixels */

    /* starting/ending y pos of the wall slice */
    int y0 = (int)((SY - wh)/2.0);
    int y1 = y0 + wh - 1;

    /* needs clipping */
    int ystart = max(0, y0);
    int yend = min(SY-1, y1);

	//바닥
	for( int y=yend; y<SY - 1; y++ )
	{
		game->img.data[SX * y + x] = 0xC0C0C0; // x, y
	}

	//벽
	for( int y=ystart; y<yend; y++ )
	{
		game->img.data[SX * y + x] = color;
	}
	//printf("\nwh: %d, y0 : %d, y1 : %d, ystart : %d , yend : %d\n", wh, y0, y1, ystart, yend);
}


void    gr_clear(t_game *g) {
    for( int x=0; x<SX; x++ ) {
        for( int y=0; y<SY; y++) {
           g->img.data[SX * y + x] = 0x000000;
        }
    }
}

static int get_color(dir_t wdir)
{
    int color;

     if (wdir == DIR_E)
		color = 0xCCAAAA;
	else if (wdir == DIR_W)
		color = 0xAACCAA;
	else if (wdir == DIR_N)
		color = 0xAAAACC;
	else if (wdir == DIR_S)
		color = 0xBBBBBB;
    return (color);
}

void render(t_game* game)
{
    gr_clear(game);
	for( int x=0; x<SX; x++ ) {
        dir_t wdir;
        double wdist = cast_single_ray(x, game->px, game->py, game->th, &wdir);
		draw_wall(game, wdist, x, get_color(wdir));  
    }
    //gr_flush(gr);
}

void player_rotate( t_game* pp, double th )
{
    pp->th += th;
    if( pp->th < 0 ) pp->th += T2PI;
    else if( pp->th > T2PI ) pp->th -= T2PI;
}


static int get_move_offset( double th, int key, double amt, double* pdx, double* pdy )
{
    switch( key ) {
        case KEY_W:
        case KEY_S:
            *pdx = (key==KEY_W ? 1 : -1) * amt * cos(th);
            *pdy = (key==KEY_W ? 1 : -1) * amt * sin(th);
            break;
        case KEY_A:
        case KEY_D:
            *pdx = amt * cos(th + (key==KEY_A ? 1 : -1) * M_PI_2);
            *pdy = amt * sin(th + (key==KEY_A ? 1 : -1) * M_PI_2);
            break;
        default: /* invalid */
            return -1;
    }
    return 0;
}

int player_move( t_game* pp, int key, double amt )
{
    double dx=0, dy=0;
    double nx, ny;

    if( get_move_offset(pp->th, key, amt, &dx, &dy) < 0 ) {
        fprintf(stderr,"gameayer_move: invalid key %d\n", key);
        return -1;
    }
    nx = pp->px + dx;
    ny = pp->py + dy;

    if( map_get_cell((int)nx, (int)ny) != 0 ) {
        printf("** bump !\n");
        return -1;
    }
    pp->px = nx;
    pp->py = ny;
    return 0;
}

int key_press(int key, t_game *game)
{
        printf("test1\n");
        if( key < 0 || key == KEY_ESC ) {   /* quit */
            printf("test1\n");
            exit(0);
        }
        if( key == KEY_LEFT || key == KEY_RIGHT ) {
                printf("test2`\n");
            player_rotate(game, ROT_UNIT * (key==KEY_LEFT ? 1 : -1));
            render(game);
        }
        else if( key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D ) {
                printf("test3\n");
            if( player_move(game, key, MOVE_UNIT) == 0 ) {
                render(game);
            }
        }
        printf("test4\n");
        return 0;
}

int        draw_loop(t_game *game)
{
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
    return (0);
}

int main( int ac, char** av )
{
    if( ac != 4 ) {
        fprintf(stderr,"usage: %s x y th(deg)\n", av[0]);
        exit(1);
    }
    t_game	game;
	game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, SX, SY, "cub3D");

    double px, py, th;
    game.px = atof(av[1]);
    game.py = atof(av[2]);
    game.th = deg2rad(atof(av[3]));

    game.img.img = mlx_new_image(game.mlx, SX, SY);
    game.img.data = (int *)mlx_get_data_addr(game.img.img, &game.img.bpp, &game.img.line_size, &game.img.endian);

    //

	// for( int x=0; x<SX; x++ ) {
    //     dir_t wdir;
    //     double wdist = cast_single_ray(x, game.px, game.py, game.th, &wdir);
	// 	draw_wall(&game, wdist, x, 0xFF0000);  
    // }
    render(&game);

	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
    mlx_loop_hook(game.mlx, draw_loop, &game);


    mlx_loop(game.mlx);
    return (0);
}
