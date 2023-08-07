/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_op_dic_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 02:57:27 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/05 23:40:08 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_dic	*ft_pagenew(int key, char *value, int pipe)
{
	t_dic	*head;

	head = ft_malloc(sizeof(t_dic), 1);
	if (!head)
		exit(UNSPECIFIED_ERROR);
	head->key = key;
	head->special = 0;
	head->pipe = pipe;
	head->value = value;
	head->next = NULL;
	head->previous = NULL;
	return (head);
}

t_parsing_output	*ft_newpipe(int in, int out, char **cmd)
{
	t_parsing_output	*head;

	head = ft_malloc(sizeof(t_parsing_output), 1);
	if (!head)
		exit(UNSPECIFIED_ERROR);
	head->fd_infile = in;
	head->fd_outfile = out;
	head->cmd = cmd;
	head->next = NULL;
	return (head);
}

void	ft_del_page_core(t_dic **dic, t_dic *ptr)
{
	t_dic	*prev;
	t_dic	*next;

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
	else if (prev)
		prev->next = NULL;
}

void	ft_del_page(t_dic **dic, t_dic *page)
{
	t_dic	*ptr;

	if (*dic == page)
	{
		*dic = (*dic)->next;
		(*dic)->previous = NULL;
	}
	ptr = *dic;
	while (ptr)
	{
		if (ptr == page)
		{
			ft_del_page_core(dic, ptr);
			break ;
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
