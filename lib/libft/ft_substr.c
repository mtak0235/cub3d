/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 02:42:04 by mtak              #+#    #+#             */
/*   Updated: 2021/01/14 03:51:32 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*extract;
	unsigned int	s_len;

	s_len = ft_strlen(s);
	if (!s)
		return (0);
	if (s_len <= start)
		return (ft_strdup(""));
	if (!(extract = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	ft_strlcpy(extract, &s[start], len + 1);
	return (extract);
}
