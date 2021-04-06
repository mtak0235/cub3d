/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 05:09:00 by mtak              #+#    #+#             */
/*   Updated: 2021/01/12 08:02:24 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*cur;
	t_list	*new_head;
	t_list	*new_next;

	if (!lst || !f)
		return (NULL);
	if (!(new_head = ft_lstnew(f(lst->content))))
		return (NULL);
	lst = lst->next;
	cur = new_head;
	while (lst)
	{
		if (!(new_next = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&new_head, del);
			return (NULL);
		}
		cur->next = new_next;
		cur = new_next;
		lst = lst->next;
	}
	return (new_head);
}
