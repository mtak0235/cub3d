/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 02:11:13 by mtak              #+#    #+#             */
/*   Updated: 2021/01/11 11:48:23 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_calloc(size_t cnt, size_t size)
{
	void	*ret;

	ret = (void *)malloc(cnt * size);
	if (!ret)
		return (NULL);
	ft_memset(ret, 0, cnt * size);
	return (ret);
}
