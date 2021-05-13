/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 08:36:31 by mtak              #+#    #+#             */
/*   Updated: 2021/05/06 19:53:15 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int s_len;

	s_len = ft_strlen(s);
	if (c == '\0')
		return ((char *)s + s_len);
	while (s_len + 1 > 0)
	{
		if (s[s_len] == (char)c)
			return (char *)s + s_len;
		s_len--;
	}
	return (0);
}
