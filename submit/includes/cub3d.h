#ifndef CUB3D_H
# define CUB3D_H

# include "./mlx.h"
# include "./libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <stdbool.h>


# define TEXTURES				8

# define C_R					6
# define C_NO					0
# define C_SO					1
# define C_WE					2
# define C_EA					3
# define C_S					4

# define C_F 					8
# define C_C					9
# define C_MAP					10

typedef struct	s_pos
{
	double		x;
	double		y;
}				t_pos;

typedef struct	s_index
{
	int			x;
	int			y;
}				t_index;

typedef struct	s_img
{
	void		*img;
	int			*data;
	int			bpp;
	int			size_l;
	int			endian;
	int			img_width;
	int			img_height;
}				t_img;

typedef struct	s_sprite
{
	int			content;
	t_pos		verthit;
	t_pos		horzhit;
	t_pos		hit;
	t_pos		mappos;
	t_pos		mapcenter;
	double		angle;
	double		min_angle;
	double		max_angle;
	double		distance;
	double		height;
	int			tex_x;
}				t_sprite;

typedef struct	s_player
{
	float		x;
	float		y;
	float		width;
	float		height;
	int			turndirection;
	int			walkdirection;
	int			walkdirection_lr;
	float		rotationangle;
	float		walkspeed;
	float		turnspeed;
	double		rotationspeed;
	double		eyelevel;
}				t_player;

typedef struct	s_ray
{
	double		rayangle;
	double		distance;
	t_pos		wallhit;
	t_sprite	sprite;
	int			washitvertical;
	int			isup;
	int			isdown;
	int			isleft;
	int			isright;
	int			wallhitcontent;
}				t_ray;

typedef struct	s_tex
{
	char		*tex_path;
	int			*texture;
	double		width;
	double		height;
}				t_tex;

typedef struct	s_config
{
	int			width;
	int			height;
	int			rows;
	int			colums;
	double		tile;
	t_tex		tex[TEXTURES];
	int			floor_color;
	int			ceiling_color;
	char		**map;
	double		rotation_speed;
	double		updown_speed;
	double		move_speed;
	double		eyelevel;
	double		fov;
	int			tuna;
	int			t_num;
}				t_config;

typedef struct	s_game
{
	t_config	config;
	void		*mlx;
	void		*win;
	t_img		img;
	t_player	player;
}				t_game;
#endif
