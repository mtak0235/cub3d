/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 23:55:27 by mtak              #+#    #+#             */
/*   Updated: 2021/05/15 19:06:30 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_resolution(t_game *game, char *line)
{
	int		i;
	int		max_width;
	int		max_height;

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
	if (i != ft_strlen(line))
		return (0);
	mlx_get_screen_size(game->mlx, &max_width, &max_height);
	game->config.width = (game->config.width > max_width) ? max_width : game->config.width;
	game->config.height = (game->config.height > max_height) ? max_height: game->config.height;
	return (1); 
}

static char	*parse_path(char *line)
{
	int		i;
	char	*buff;

	i = 0;
	while (is_upper(line[i]))
		i++;
	while (is_space(line[i]))
		i++;
	buff = ft_strdup(line + i);
	return (buff);
}

static int	parse_color(char *line)
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
	if (is_space(line[i]))
		i++;
	j = -1;
	while (line[i] && ++j < 3)
	{
		while (line[i] && ft_isdigit(line[i]))
			colors[j] = colors[j] * 10 + line[i++] - 48;
		if (colors[j] > 255 || colors[j] < 0)
			return (-1);
		while (is_space(line[i]))
			i++;
		ft_strchr(",", line[i]) ? i++ : 0;
		while (is_space(line[i]))
			i++;
	}
	color = colors[0] * 256 * 256 + colors[1] * 256 + colors[2];
	return (color);
}

static int	parse_map(t_config *config, char *temp)
{
	int		i;
	int		j;

	if (!(config->map = ft_split(temp, '\n'))) /* 여기가 바로 c->map != 0이 할당되는 곳이다*/
		return (0);
	config->i = 1;
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

int			parse_by_type(int ret, t_game *game, int tp, char *line)
{
	static char *temp = "";

	if (tp == C_R)
	{
		if (!parse_resolution(game, line))
			return (free_line(line, 0));
	}
	else if (tp >= C_NO && tp <= C_S)
	{
		if (game->config.tex[tp].tex_path || !(game->config.tex[tp].tex_path = parse_path(line)))
			return (free_line(line, 0));
	}
	else if (tp == C_F || tp == C_C)
	{
		if ((tp == C_F && (game->config.floor_color = parse_color(line)) == -1) ||
		(tp == C_C && (game->config.ceiling_color = parse_color(line)) == -1))
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
