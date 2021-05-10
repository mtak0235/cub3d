/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 23:56:14 by mtak              #+#    #+#             */
/*   Updated: 2021/05/10 23:56:17 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	*load_image(t_game *game, char *path, t_img *img, int i)
{
	int		x;
	int		y;
	int		*res;

	if (!(img->img = mlx_xpm_file_to_image(game->mlx,
					path, &img->img_width, &img->img_height)))
		exit_error(game, EXIT_FAILURE, "ERROR\nwrong texture");
	game->config.tex[i].width = img->img_width;
	game->config.tex[i].height = img->img_height;
	img->data = (int *)mlx_get_data_addr(img->img,
			&img->bpp, &img->size_l, &img->endian);
	res = (int *)malloc(sizeof(int) * (img->img_width * img->img_height));
	y = -1;
	while (++y < img->img_height)
	{
		x = -1;
		while (++x < img->img_width)
		{
			res[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(game->mlx, img->img);
	return (res);
}

void		load_texture(t_game *game)
{
	int		i;
	t_img	img;

	i = -1;
	while (++i < TEXTURES - 3)
	{
		game->config.tex[i].texture =
			load_image(game, game->config.tex[i].tex_path, &img, i);
		free(game->config.tex[i].tex_path);
	}
}
