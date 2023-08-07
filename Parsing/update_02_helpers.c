/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_02_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 22:11:57 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/06 02:35:16 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_delete_pages(t_dic **dic, t_dic *ptr, int i, int j)
{
	if (i == 1)
		ft_del_page(dic, ptr->previous->previous);
	ft_del_page(dic, ptr->previous);
	if (j == 1)
		ft_del_page(dic, ptr->next);
}

void	ft_prepre_update_02(t_dic **dic, t_dic **ptr)
{
	(*ptr)->next->special = (*ptr)->key;
	(*ptr) = (*ptr)->next;
	ft_delete_pages(dic, (*ptr), 0, 1);
	if ((*ptr)->next && (*ptr)->next->key == CMD)
	{
		(*ptr)->next->value = ft_strjoin((*ptr)->value, (*ptr)->next->value, 1);
		(*ptr) = (*ptr)->next;
		ft_del_page(dic, (*ptr)->previous);
	}
	else if ((*ptr)->next && ((*ptr)->next->key == DQUOTE
			|| (*ptr)->next->key == SQUOTE))
	{
		(*ptr)->next->next->value = ft_strjoin((*ptr)->value,
				(*ptr)->next->next->value, 1);
		(*ptr) = (*ptr)->next->next;
		ft_delete_pages(dic, (*ptr), 1, 1);
	}
}

void	ft_pre_update_02(t_dic **dic, t_dic **ptr)
{
	if ((*ptr)->key == DQUOTE || (*ptr)->key == SQUOTE)
	{
		ft_prepre_update_02(dic, ptr);
		while ((*ptr)->next && (*ptr)->next->key == CMD)
		{
			(*ptr)->next->value = ft_strjoin((*ptr)->value, (*ptr)->next->value,
					1);
			ft_pre_update_02_core_01(dic, ptr);
		}
		while ((*ptr)->next && (*ptr)->next->key == DOLLAR)
		{
			(*ptr)->next->next->value = ft_strjoin((*ptr)->value,
					(*ptr)->next->next->value, 1);
			(*ptr) = (*ptr)->next->next;
			ft_delete_pages(dic, (*ptr), 1, 0);
		}
		while ((*ptr)->next && ((*ptr)->next->key == DQUOTE
				|| (*ptr)->next->key == SQUOTE))
		{
			(*ptr)->next->next->value = ft_strjoin((*ptr)->value,
					(*ptr)->next->next->value, 1);
			(*ptr) = (*ptr)->next->next;
			ft_delete_pages(dic, (*ptr), 1, 1);
		}
	}
}

void	ft_update_02_quotes(t_dic **dic, t_dic **ptr)
{
	if ((*ptr)->previous && (*ptr)->previous->key == CMD)
	{
		(*ptr)->next->value = ft_strjoin((*ptr)->previous->value,
				(*ptr)->next->value, 1);
		(*ptr) = (*ptr)->next;
		ft_delete_pages(dic, *ptr, 1, 1);
		return ;
	}
	*ptr = (*ptr)->next;
	ft_delete_pages(dic, *ptr, 0, 1);
}

void	ft_update_02_dolcmd(t_dic **dic, t_dic **ptr)
{
	(*ptr)->next->value = ft_strjoin((*ptr)->previous->value,
			(*ptr)->next->value, 1);
	*ptr = (*ptr)->next;
	ft_delete_pages(dic, *ptr, 1, 0);
}
