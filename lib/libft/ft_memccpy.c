/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 07:55:22 by mtak              #+#    #+#             */
/*   Updated: 2021/01/11 14:42:10 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*new_dst;
	const unsigned char	*new_src;

	new_dst = dst;
	new_src = src;
	while (n--)
	{
		if (*new_src == (unsigned char)c)
		{
			*new_dst = *new_src;
			return ((void *)++new_dst);
		}
		*new_dst++ = *new_src++;
	}
	return (NULL);
}
