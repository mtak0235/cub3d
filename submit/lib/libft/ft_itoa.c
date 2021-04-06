/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 02:10:50 by mtak              #+#    #+#             */
/*   Updated: 2021/01/12 09:19:37 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_len(long int n)
{
	int	len;

	len = n <= 0 ? 1 : 0;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int a)
{
	char		*ret;
	int			sign;
	int			len;
	long int	n;

	n = a;
	sign = n < 0 ? -1 : 1;
	len = ft_itoa_len(n);
	if (!(ret = (char *)malloc(sizeof(char) * len + 1)))
		return (0);
	ret[len] = 0;
	len--;
	n *= sign;
	while (len >= 0)
	{
		ret[len--] = 48 + n % 10;
		n /= 10;
	}
	if (sign == -1)
		ret[0] = '-';
	return (ret);
}
