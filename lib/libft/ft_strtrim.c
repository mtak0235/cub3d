/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 09:21:54 by mtak              #+#    #+#             */
/*   Updated: 2021/01/11 11:44:32 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s, char const *set)
{
	char	*ret;
	size_t	start;
	size_t	end;

	if (!s)
		return (NULL);
	if (!set)
		return (ft_strdup(s));
	start = 0;
	end = ft_strlen(s);
	while (s[start] && ft_strchr(set, s[start]))
		start++;
	while (s[end - 1] && ft_strchr(set, s[end - 1]))
	{
		if (end - 1 < 1)
			break ;
		end--;
	}
	if (start > end)
		return (ft_strdup(""));
	if (!(ret = (char *)malloc(sizeof(char) * (end - start + 1))))
		return (NULL);
	ft_strlcpy(ret, s + start, end - start + 1);
	return (ret);
}
