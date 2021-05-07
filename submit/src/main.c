/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:21:05 by mtak              #+#    #+#             */
/*   Updated: 2021/05/07 13:56:55 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
int check_validation()
{

}

int is_space(char c)
{
	if (c == " ")
		return (1);
	return (0);
}

int is_upper(char c)
{
	if ('A' <= c && c <= 'Z')
		return (1);
	return (0);
}

static int parse_color(char *line)
{
	int color;
	int colors[3];
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < 3) 
		colors[j] = 0;
	while (is_upper(line[i]))
		i++;
	while (is_space(line[i]))
		i++;
	j = -1;
	while (line[i] && ++j < 3)
	{
		while (line[i] && ft_isdigit(line[i]))
			colors[j] = colors[j] * 10 + line[i++] - 48;
		if ((!ft_strchr(",", line[i]) && line[i] != '\0') || 
		!(0 <= colors[j] && colors[j] <= 255))
			return (-1);
		ft_strchr(",", line[i]) ? i++ : 0;
	}
	color = colors[0] << 16 + colors[1] << 8 + colors[2];
	return (color);
}

static char *parse_path(char *line)
{
	char **tmp;
	char *path;

	tmp = ft_split(line, " ");
	path = ft_strdup(tmp[1]);
	ft_free(tmp);
	return (path);
}

int free_line(char *line, int ret)
{
	free(line);
	return (ret);
}

static int parse_resolution(t_config *config, char *line)
{
	char **tmp;

	tmp = ft_split(line, " ");
	config->width = ft_atoi(tmp[1]);
	config->height = ft_atoi(tmp[2]);
	ft_free(tmp);
	return (1);
}

int parse_by_type(int ret, t_config *config, int type, char *line)
{
	static char *tmp;

	tmp = "";
	if (type == C_R)
	{
		if (!parse_resolution(config, line))		
			return (free_line(line, 0));
	}
	else if (C_NO <= type && type <= C_S)
	{
		if (config->tex[type].tex_path || !(config->tex[type].tex_path = parse_path(line)))
			return (free_line(line, 0));
	}
	else if (type == C_F && type == C_C)
	{
		if ((type == C_F && (config->floor_color = parse_color(line)) == -1) ||
		(type == C_C && (config->ceiling_color = parse_color(line)) == -1))
			return (free_line(line, 0));
	}
	else
	{
		tmp = update_temp(tmp, line);
		if (!ret && !parse_map(config, tmp))
			
	}
	return (free_line(line, 1));
}

static int is_blank_line(char *line)
{
	int i;

	i = 0;
	while (line[i] != 0)
	{
		if (!((9 <= line[i] && line[i] <= 13)  || line[i] == 32))
			return (0);
		i++;
	}
	return (1);
}

int check_map_component(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr("012NSEW", line[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

static int check_type(char *line)
{
	if (line[0] == 'R' && line[1] == ' ')
		return (C_R);
	else if (line[0] == 'N' && line[1] == 'O')
		return (C_NO);
	else if (line[0] == 'S' && line[1] == 'O')
		return (C_SO);
	else if (line[0] == 'W' && line[1] == 'E')
		return (C_WE);
	else if (line[0] == 'E' && line[1] == 'A')
		return (C_EA);
	else if (line[0] == 'S' && line[1] == ' ')
		return (C_S);
	else if (line[0] == 'F' && line[1] == ' ')
		return (C_F);
	else if (line[0] == 'C' && line[1] == ' ')
		return (C_C);
	else if (check_map_component(line))
		return (C_MAP);
	return (-1);
}

int is_cub_file(char *path)
{
	int len;
	int ret;

	len = ft_strlen(path);
	ret = 1;
	if (len >= 4)
		ret = ft_strncmp(path + len - 4, ".cub", 4);
	if (ret == 0)
		return (1);
	else
		return (0);
}

int parse_config(t_game *game,t_config *config, char *path)
{
	int type;
	char *line;
	int fd;
	int ret;
	
	if (!(is_cub_file(path)))
		return (exit_error(game, "ERROR\n it is not .cub extension"));
	if ((fd = open(path, O_RDONLY)) < 0)
		return (exit_error(game, "ERROR\n wrong path"));
	ret = 1;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if ((type = check_type(line)) == -1)
			return (exit_error(game, "ERROR\nwrong type"));
		if (is_blank_line(line) && !(config->map))
		{
			free(line);
			continue;
		}
		else if(is_blank_line(line) && config->map && ret)
			return (exit_error(game, "ERROR\n blank line in the map"));
		if (!parse_by_type(ret, config, type, line))
			return (0);
	}
	parse_by_type(ret, config, type, line);
	close(fd);
	return (1);
}
void init(t_game *game)
{
	int i;

	i = 0;
	while (i < TEXTURES)
		game->config.tex[i++].tex_path = NULL;
	game->config.width = 0;
	game->config.height = 0;
	game->config.rows = 0;
	game->config.colums = 0;
	game->config.tile = 0;
	game->config.floor_color = 0;
	game->config.ceiling_color = 0;
	game->config.map = NULL;
	game->config.rotation_speed = .11;
	game->config.move_speed = .11;
	game->config.updown_speed = 30;
	game->config.eyelevel = 0;
	game->config.fov = 80 * M_PI / 180;

	game->player.x = 0;
	game->player.y = 0;
	game->player.width = 0;
	game->player.height = 0;
	game->player.turndirection = 0;
	game->player.walkdirection = 0;
	game->player.walkdirection_lr = 0;
	game->player.rotationangle = M_PI / 2;
	game->player.walkspeed = 5;
	game->player.turnspeed = 3 * (M_PI / 180);
	game->player.rotationspeed = 0;
	game->player.eyelevel = 0;
}

void free_game(t_game *game)
{
	int i;

	i = 0;
	while (i < game->config.rows)
	{
		if (game->config.map[i])
			free(game->config.map[i]);
		i++;
	}
	free(game->config.map);
	i = 0;
	while (i < TEXTURES - 3)
	{
		if (game->config.tex[i].texture)
			free(game->config.tex[i].texture);
		i++;
	}
}

int exit_error(t_game *game, char *err_str)
{
	if (err_str)
		write(1, err_str, ft_strlen(err_str));
	exit(EXIT_FAILURE);
	free_game(game);
	return (EXIT_FAILURE);
}

int main(int ac, char **av)
{
	t_game game;
	
	if (!(ac == 2 || (ac == 3 && !ft_strncmp(av[2], "--save", 6))))
		return (exit_error(&game, "ERROR\nargument error"));
	init(&game);
	if (!parse_config(&game, &game.config, av[1]))
		exit_error(&game, "ERROR\nparsed map error");
	if (!check_map_validation())
		exit_error(&game, "ERROR\nmap is not valid");
	if ()
}