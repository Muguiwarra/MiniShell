/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <ibel-har@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:35:57 by ibel-har          #+#    #+#             */
/*   Updated: 2022/11/12 18:52:21 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*cursor;
	t_list	*head;
	t_list	*new_n;

	cursor = lst;
	head = NULL;
	new_n = NULL;
	if (lst && f && del)
	{
		while (cursor)
		{
			new_n = ft_lstnew(f(cursor->content));
			if (!new_n)
			{
				ft_lstclear(&head, del);
				return (0);
			}
			ft_lstadd_back(&head, new_n);
			cursor = cursor->next;
		}
		return (head);
	}
	return (NULL);
}
