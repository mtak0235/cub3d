/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 17:01:31 by mtak              #+#    #+#             */
/*   Updated: 2021/05/20 13:16:26 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	pass_space(const char *str, int *i)
{
	while (*str == 32 || (9 <= *str && *str <= 13))
	{
		str++;
		(*i)++;
	}
}

int			ft_atoi(const char *str, int *i)
{
	int		sign;
	size_t	num;

	pass_space(str, i);
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
		(*i)++;
	}
	num = 0;
	while (48 <= *str && *str <= 57)
	{
		num *= 10;
		num = num + *str - 48;
		str++;
		(*i)++;
	}
	if (num > LLONG_MAX - 1 && sign == 1)
		return (-1);
	if (num > LLONG_MAX && sign == -1)
		return (-1);
	return (sign * num);
}
