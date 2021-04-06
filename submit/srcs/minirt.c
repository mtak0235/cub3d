#include "mlx.h"
#include <stdio.h>

int deal_key(int key, void *param)
{
	printf("mtak\n");
	return 0;
}

int             main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 600, "Hello 42!");
	mlx_key_hook(mlx_win, deal_key, (void *)0);
	mlx_hook(mlx_win, 2, 1L << 0, deal_key, (void *)0);
	printf("wow\n");
	mlx_loop(mlx);
	return (0);
}
