/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_op_dic_00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 03:57:10 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/06 04:35:29 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parsing_output	*ft_lastpipe(t_parsing_output *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

void	ft_addpage_back(t_dic **lst, t_dic *new)
{
	t_dic	*ptr1;
	t_dic	*ptr2;

	if (*lst)
	{
		ptr1 = ft_lastpage(*lst);
		ptr1->next = new;
		ptr1 = *lst;
		ptr2 = *lst;
		while (ptr1)
		{
			ptr1 = ptr1->next;
			if (ptr1)
				ptr1->previous = ptr2;
			ptr2 = ptr1;
		}
	}
	else
		*lst = new;
}

void	ft_addpipe_back(t_parsing_output **lst, t_parsing_output *new)
{
	t_parsing_output	*ptr1;

	if (*lst)
	{
		ptr1 = ft_lastpipe(*lst);
		ptr1->next = new;
	}
	else
		*lst = new;
}

void	ft_rm_multi_sp(t_dic **dic)
{
	t_dic	*ptr;

	ptr = *dic;
	while (ptr && ptr->key == SPACES)
	{
		if (ptr->next)
		{
			ptr = ptr->next;
			ft_del_page(dic, ptr->previous);
		}
		else
			break ;
	}
	while (ptr)
	{
		if (ptr->key == SPACES)
		{
			while (ptr->next && ptr->next->key == SPACES)
			{
				ptr = ptr->next;
				ft_del_page(dic, ptr->previous);
			}
		}
		ptr = ptr->next;
	}
}
