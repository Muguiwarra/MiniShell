/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <ibel-har@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 22:50:41 by ibel-har          #+#    #+#             */
/*   Updated: 2022/11/12 18:51:42 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cursor;
	t_list	*next_n;

	cursor = NULL;
	next_n = NULL;
	if (lst && *lst && del)
	{	
		cursor = *lst;
		next_n = cursor->next;
		while (cursor)
		{
			next_n = cursor->next;
			ft_lstdelone(cursor, del);
			cursor = next_n;
		}
		*lst = NULL;
	}
}
