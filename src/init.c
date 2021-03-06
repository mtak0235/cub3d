/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 23:54:27 by mtak              #+#    #+#             */
/*   Updated: 2021/05/18 10:51:18 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_game *game)
{
	game->player.x = 0;
	game->player.y = 0;
	game->player.width = 0;
	game->player.height = 0;
	game->player.turndirection = 0;
	game->player.walkdirection = 0;
	game->player.walkdirection_lr = 0;
	game->player.rotationangle = M_PI / 2;
	game->player.walkspeed = 20;
	game->player.turnspeed = 7 * (M_PI / 180);
	game->player.rotationspeed = 0;
	game->player.eyelevel = 0;
}

void	init_config(t_game *game)
{
	int i;

	game->config.width = 0;
	game->config.height = 0;
	game->config.rows = 0;
	game->config.colums = 0;
	game->config.tile = 0;
	i = 0;
	while (i < TEXTURES)
		game->config.tex[i++].tex_path = NULL;
	game->config.floor_color = 0;
	game->config.ceiling_color = 0;
	game->config.map = NULL;
	game->config.rotation_speed = .11;
	game->config.move_speed = .11;
	game->config.updown_speed = 50;
	game->config.eyelevel = 0;
	game->config.fov = 80 * M_PI / 180;
	game->config.i = 0;
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx,
			game->config.width, game->config.height, "cub3d");
	game->img.img = mlx_new_image(game->mlx,
			game->config.width, game->config.height);
	game->img.data = (int *)mlx_get_data_addr(game->img.img,
			&game->img.bpp, &game->img.size_l, &game->img.endian);
}
