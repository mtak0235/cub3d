/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:16:57 by mtak              #+#    #+#             */
/*   Updated: 2021/05/17 19:44:18 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		space_pass(char *line, int *i)
{
	if (is_space(line[*i]))
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int		is_valid_color(int *j, int colors[])
{
	while ((*j)--)
	{
		if (colors[*j] > 255 || colors[*j] < 0)
			return (0);
	}
	return (1);
}

void	trim_comma(char *line, int *i, int *j)
{
	if (ft_strchr(",", line[*i]))
	{
		(*i)++;
		(*j)++;
	}
}

int		type_c_d(t_game *game, char *line, int tp)
{
	if (game->config.tex[tp].tex_path
		|| !(game->config.tex[tp].tex_path = parse_path(line)))
		return (1);
	return (0);
}

int		type_c_fc(t_game *game, char *line, int tp)
{
	if ((tp == C_F &&
	(game->config.floor_color = parse_color(line)) == -1) ||
	(tp == C_C &&
	(game->config.ceiling_color = parse_color(line)) == -1))
		return (1);
	return (0);
}
