/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_dic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 03:15:24 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/01 03:16:59 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_update_00(t_dic **dic)
{
	t_dic	*ptr1;

	ft_rm_multi_sp(dic);
	ptr1 = *dic;
	while (ptr1)
	{
		if (ptr1->key == LESSER)
		{
			if (ptr1->next && ptr1->next->key == GREATER)
				ft_del_page(dic, ptr1->next);
			ft_less_great(dic, ptr1, LESSER);
		}
		else if (ptr1->key == GREATER)
			ft_less_great(dic, ptr1, GREATER);
		else if (ptr1->key == PIPE)
		{
			if (!ptr1->next || !ptr1->previous)
				g_glob.exit_status = SYNTAX_ERROR;
		}
		ptr1 = ptr1->next;
	}
}

void	ft_update_03(t_dic **dic)
{
	t_dic	*ptr;

	ptr = *dic;
	if (ptr->key == SPACE || ptr->key == DQUOTE || ptr->key == SQUOTE
		|| ptr->key == DOLLAR || ptr->key == LESSER || ptr->key == GREATER
		|| ptr->key == APPEND)
	{
		if (ptr->key == DQUOTE || ptr->key == SQUOTE || ptr->key == APPEND)
			ptr->next->special = ptr->key;
		ft_del_page(dic, ptr);
	}
	ptr = *dic;
	while (ptr)
	{
		if (ptr->key == SPACE || ptr->key == DQUOTE || ptr->key == SQUOTE
			|| ptr->key == DOLLAR || ptr->key == LESSER || ptr->key == GREATER
			|| ptr->key == APPEND)
		{
			if (ptr->key == DQUOTE || ptr->key == SQUOTE || ptr->key == APPEND)
				if (ptr->next)
					ptr->next->special = ptr->key;
			ft_del_page(dic, ptr);
		}
		ptr = ptr->next;
	}
}
