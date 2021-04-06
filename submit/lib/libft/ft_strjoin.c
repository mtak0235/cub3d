/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 05:39:59 by mtak              #+#    #+#             */
/*   Updated: 2021/01/11 14:51:08 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*comb_str;

	if (!s1)
		return (ft_substr(s2, 0, ft_strlen(s2)));
	if (!s2)
		return (0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (!(comb_str = (char *)malloc(sizeof(char) * (len_s1 + len_s2) + 1)))
		return (0);
	ft_memcpy(comb_str, s1, len_s1);
	ft_memcpy(comb_str + len_s1, s2, len_s2);
	comb_str[len_s1 + len_s2] = 0;
	return (comb_str);
}
