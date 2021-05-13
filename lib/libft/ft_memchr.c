/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 01:28:19 by mtak              #+#    #+#             */
/*   Updated: 2021/01/11 14:13:56 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *dst, int c, size_t n)
{
	while (n--)
	{
		if (*(const unsigned char *)dst == (unsigned char)c)
			return ((void *)dst);
		dst++;
	}
	return (0);
}
