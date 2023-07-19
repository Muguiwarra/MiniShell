/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_op_dic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 03:57:10 by nabboune          #+#    #+#             */
/*   Updated: 2023/07/19 18:43:17 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_dic	*ft_pagenew(int key, char *value, int pipe)
{
	t_dic	*head;

	head = ft_malloc(sizeof(t_dic));
	if (!head)
		exit (UNSPECIFIED_ERROR);
	head->key = key;
	head->pipe = pipe;
	head->value = value;
	head->next = NULL;
	head->previous = NULL;
	return (head);
}

void	ft_del_page(t_dic **dic, t_dic *page)
{
	t_dic	*ptr;
	t_dic	*prev;
	t_dic	*next;

	ptr = *dic;
	while(ptr)
	{
		if (ptr == page)
		{
			prev = ptr->previous;
			next = ptr->next;
			if (prev)
				prev->next = next;
			else
			{
				*dic = next;
				if (next)
					next->previous = NULL;
			}
			if (next)
				next->previous = prev;
			else
				if (prev)
					prev->next = NULL;
			break;
		}
		ptr = ptr->next;
	}
}

t_dic	*ft_lastpage(t_dic *lst)
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

void	ft_rm_sp(t_dic **dic, int i)
{
	t_dic	*ptr;

	ptr = *dic;
	while (ptr && ptr->key == SPACE)
	{
		if (ptr->next)
		{
			ptr = ptr->next;
			ft_del_page(dic, ptr->previous);
		}
		else
			break;
	}
	while (ptr)
	{
		if (i == 0 && ptr->key == SPACE)
		{
			if (ptr->next && ptr->next->key == SPACE)
			{
				ptr = ptr->next;
				ft_del_page(dic, ptr->previous);
			}
			else
			{
				ft_del_page(dic, ptr);
				break;
			}
		}
		else if (i == 1 && ptr->key == SPACE)
		{
			while (ptr->next && ptr->next->key == SPACE)
			{
				ptr = ptr->next;
				ft_del_page(dic, ptr->previous);
			}
		}
		ptr = ptr->next;
	}
}
