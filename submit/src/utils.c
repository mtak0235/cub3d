/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 23:56:20 by mtak              #+#    #+#             */
/*   Updated: 2021/05/10 23:56:23 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

int		is_upper(int x)
{
	if (x >= 65 && x <= 90)
		return (1);
	return (0);
}

int		is_space(int x)
{
	if ((x >= 9 && x <= 13) || x == 32)
		return (1);
	return (0);
}
