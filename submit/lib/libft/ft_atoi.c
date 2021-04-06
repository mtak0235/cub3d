/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 17:01:31 by mtak              #+#    #+#             */
/*   Updated: 2021/01/12 07:45:21 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		sign;
	size_t	num;

	while (*str == 32 || (9 <= *str && *str <= 13))
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	num = 0;
	while (48 <= *str && *str <= 57)
	{
		num *= 10;
		num = num + *str - 48;
		str++;
	}
	if (num > LLONG_MAX - 1 && sign == 1)
		return (-1);
	if (num > LLONG_MAX && sign == -1)
		return (0);
	return (sign * num);
}
