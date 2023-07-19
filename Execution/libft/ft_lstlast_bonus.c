/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <ibel-har@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:32:44 by ibel-har          #+#    #+#             */
/*   Updated: 2022/11/12 18:52:47 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*cursor;

	cursor = NULL;
	if (!lst)
		return (cursor);
	cursor = lst;
	while (cursor->next)
		cursor = cursor->next;
	return (cursor);
}
