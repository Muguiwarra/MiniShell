/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less_great_00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 22:56:22 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/05 00:36:11 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pre_less_great(t_dic **dic, t_dic **ptr2)
{
	while (*ptr2 && (*ptr2)->key == SPACE)
		*ptr2 = (*ptr2)->next;
	if (*ptr2 && (*ptr2)->key == DOLLAR)
	{
		if ((*ptr2)->next)
		{
			*ptr2 = (*ptr2)->next;
			ft_del_page(dic, (*ptr2)->previous);
		}
	}
}

void	ft_limiter_outfile(t_dic **ptr2, int operation)
{
	if (operation == LESSER)
		(*ptr2)->key = LIMITER;
	else
		(*ptr2)->key = OUTFILE;
}

void	ft_del_move(t_dic **dic, t_dic **ptr2)
{
	ft_del_page(dic, *ptr2);
	*ptr2 = (*ptr2)->next;
}

void	ft_op_less_great(t_dic **dic, t_dic **ptr2, t_dic **ptr1, int operation)
{
	while ((*ptr2)->next && (*ptr2)->next->key == SPACE)
		ft_del_move(dic, ptr2);
	if ((*ptr2)->next && (*ptr2)->next->key != LESSER
		&& (*ptr2)->next->key != GREATER)
	{
		if ((*ptr2)->next->key == DQUOTE || (*ptr2)->next->key == SQUOTE)
		{
			ft_del_page(dic, (*ptr2)->next);
			ft_del_page(dic, (*ptr2)->next->next);
		}
		ft_del_page(dic, *ptr2);
		if (operation == LESSER)
			(*ptr1)->key = HEREDOC;
		else
			(*ptr1)->key = APPEND;
		*ptr2 = (*ptr1)->next;
		if (*ptr2)
			ft_limiter_outfile(ptr2, operation);
		else
			g_glob.exit_status = SYNTAX_ERROR;
	}
	else
		g_glob.exit_status = SYNTAX_ERROR;
}

int		ft_op_dquote_cond(t_dic **ptr2, int i, int j)
{
	if ((*ptr2)->next->value[i + j + 1]
		&& ft_is_delimiter((*ptr2)->next->value[i + j
			+ 1]) != SPACE
		&& ft_is_delimiter((*ptr2)->next->value[i + j
			+ 1]) != DQUOTE)
		return (1);
	return (0);
}
