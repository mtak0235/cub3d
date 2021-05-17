/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 23:55:27 by mtak              #+#    #+#             */
/*   Updated: 2021/05/17 20:03:12 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		parse_resolution(t_game *game, char *line)
{
	int			i;
	int			mw;
	int			mh;

	i = 0;
	while (is_upper(line[i]))
		i++;
	while (is_space(line[i]))
		i++;
	while (ft_isdigit(line[i]))
		game->config.width = game->config.width * 10 + line[i++] - 48;
	while (is_space(line[i]))
		i++;
	while (ft_isdigit(line[i]))
		game->config.height = game->config.height * 10 + line[i++] - 48;
	if (i != (int)ft_strlen(line))
		return (0);
	mlx_get_screen_size(game->mlx, &mw, &mh);
	game->config.width = (game->config.width > (unsigned int)mw)
	? mw : game->config.width;
	game->config.height = (game->config.height > (unsigned int)mh)
	? mh : game->config.height;
	return (1);
}

char			*parse_path(char *line)
{
	int			i;
	char		*buff;

	i = 0;
	while (is_upper(line[i]))
		i++;
	while (is_space(line[i]))
		i++;
	buff = ft_strdup(line + i);
	return (buff);
}

int				parse_color(char *line)
{
	int	i;
	int	j;
	int	color;
	int	colors[3];

	i = 0;
	j = 0;
	while (j < 3)
		colors[j++] = 0;
	while (is_upper(line[i]))
		i++;
	j = 0;
	while (line[i] && j < 3)
	{
		if (space_pass(line, &i))
			continue;
		if (line[i] && ft_isdigit(line[i]))
			colors[j] = colors[j] * 10 + line[i++] - 48;
		trim_comma(line, &i, &j);
	}
	if (!is_valid_color(&j, colors))
		return (-1);
	color = colors[0] * 256 * 256 + colors[1] * 256 + colors[2];
	return (color);
}

static int		parse_map(t_config *config, char *temp)
{
	int			i;
	int			j;

	if (!(config->map = ft_split(temp, '\n')))
		return (0);
	free(temp);
	i = -1;
	j = 0;
	while (config->map[++i])
		j = j < (int)ft_strlen(config->map[i])
			? (int)ft_strlen(config->map[i]) : j;
	config->rows = i;
	config->colums = j;
	config->tile = config->width / config->colums;
	return (1);
}

int				parse_by_type(int ret, t_game *game, int tp, char *line)
{
	static char *temp = "";

	if (tp == C_R)
	{
		if (!parse_resolution(game, line))
			return (free_line(line, 0));
	}
	else if (tp >= C_NO && tp <= C_S)
	{
		if (type_c_d(game, line, tp))
			return (free_line(line, 0));
	}
	else if (tp == C_F || tp == C_C)
	{
		if (type_c_fc(game, line, tp))
			return (free_line(line, 0));
	}
	else
	{
		temp = update_temp(temp, line);
		game->config.i = 1;
		if (ret == 0 && !parse_map(&game->config, temp))
			return (free_line(line, 0));
	}
	return (free_line(line, 1));
}
