/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 23:55:08 by mtak              #+#    #+#             */
/*   Updated: 2021/05/16 17:56:18 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_wall(double x, double y, t_game *game)
{
	int gridx;
	int gridy;
	
	if (x < 0 || x > game->config.width || y < 0 || y > game->config.height)
		return (1);
	gridx = (int)floor(x / game->config.tile);
	gridy = (int)floor(y / game->config.tile);
	if (gridx <= 0 || gridx >= game->config.colums
			|| gridy <= 0 || gridy >= game->config.rows)
		return (1);
	else if (game->config.map[gridy][gridx] == '1' ||
			game->config.map[gridy][gridx] == ' ' ||
			game->config.map[gridy][gridx] == '\0')
		return (1);
	// else if (game->config.map[(int)floor(++y / game->config.tile)][(int)floor(++x / game->config.tile)] == ' '||
	// 	game->config.map[(int)floor(x / game->config.tile)][(int)floor(y / game->config.tile)] == '1')
	// 	return (1);
	return (0);
}

int		is_sprite(double x, double y, t_game *game)
{
	int gridx;
	int gridy;

	if (x < 0 || x > game->config.width || y < 0 || y > game->config.height)
		return (0);
	gridx = (int)floor(x / game->config.tile);
	gridy = (int)floor(y / game->config.tile);
	if (gridx <= 0 || gridx >= game->config.colums
			|| gridy <= 0 || gridy >= game->config.rows)
		return (0);
	if (game->config.map[gridy][gridx] == '2')
		return (1);
	return (0);
}

double	normalize_angle(double angle)
{
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	while (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void	move_player(t_game *g)
{
	float	move_angle;
	float	move_step;
	t_pos	new;
	double	newlevel;

	newlevel = g->config.eyelevel + g->player.eyelevel * g->config.updown_speed;
	if (newlevel < g->config.height / 4 && newlevel > -g->config.height / 4)
		g->config.eyelevel = newlevel;
	g->player.rotationangle += g->player.turndirection * g->player.turnspeed;
	move_step = g->player.walkdirection * g->player.walkspeed;
	if (g->player.walkdirection_lr)
	{
		move_angle = normalize_angle(g->player.rotationangle
				- g->player.walkdirection_lr * M_PI / 2);
		new.x = g->player.x + cos(move_angle) * move_step;
		new.y = g->player.y + sin(move_angle) * move_step;
	}
	else
		set_pos(&new, g->player.x + cos(g->player.rotationangle) * move_step,
				g->player.y + sin(g->player.rotationangle) * move_step);
	if (!is_wall(new.x, new.y, g))
	{
		g->player.x = new.x;
		g->player.y = new.y;
	}
}
