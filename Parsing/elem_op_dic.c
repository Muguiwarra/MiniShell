/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_op_dic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 03:57:10 by nabboune          #+#    #+#             */
/*   Updated: 2023/07/19 09:24:52 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_dic	*ft_pagenew(int key, char *value)
{
	t_dic	*head;

	head = ft_malloc(sizeof(t_dic));
	if (!head)
		exit (UNSPECIFIED_ERROR);
	head->key = key;
	head->pipe = 0;
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
			if (next)
				next->previous = prev;
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
	while (ptr)
	{
		if (i == 0 && ptr->key == SPACE)
		{
			printf("$$\n");
			ptr = ptr->next;
			ft_del_page(dic, ptr->previous);
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

char	*ft_rm_end_sp(char *input)
{
	char	*output;
	int		l;
	int		i;

	i = 0;
	l = ft_strlen(input) - 1;
	while(input[l] && (input[l] == ' ' || input[l] == '\t' ||
		input[l] == '\n' || input[l] == '\v' || input[l] == '\f' ||
		input[l] == '\r'))
		l--;
	output = ft_malloc(sizeof(l));
	while (i <= l)
	{
		output[i] = input[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}

// char	*ft_rm_multi_sp(char *input)
// {
// 	int
// }