/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 17:01:31 by mtak              #+#    #+#             */
/*   Updated: 2021/05/21 11:34:22 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

static void	pass_space(char **str, int *i)
{

	while (**str == 32 || (9 <= **str && **str <= 13))
	{
		(*str)++;
		(*i)++;
	}
}

int			ft_atoi(char *str, int *i)
{
	int				sign;
	unsigned int	num;

	pass_space(&str, i);
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
	if (num > INT_MAX - 1 && sign == -1)
		return (0);
	if (num > INT_MAX && sign == -1)
		return (0);
	return (sign * num);
}
