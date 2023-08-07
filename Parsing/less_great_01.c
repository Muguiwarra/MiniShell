/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less_great_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 22:57:23 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/06 01:00:05 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_op_dquote(t_dic **ptr2)
{
	char	*var;
	int		i;
	int		j;

	if ((*ptr2)->key == DQUOTE)
	{
		i = 0;
		while ((*ptr2)->next->value[i])
		{
			j = 0;
			if ((*ptr2)->next->value[i] == '$')
			{
				while (ft_op_dquote_cond(ptr2, i, j))
					j++;
				var = ft_substr((*ptr2)->next->value, i + 1, j, 1);
				(*ptr2)->next->value = ft_replace_str((*ptr2)->next->value,
						ft_expand(var), i, i + j);
			}
			if (j != 0)
				i += j;
			else
				i++;
		}
	}
}

void	ft_op_cmd_dollar(t_dic **dic, t_dic **ptr2, int operation)
{
	if ((*ptr2)->key == DOLLAR)
	{
		*ptr2 = (*ptr2)->next;
		ft_del_page(dic, (*ptr2)->previous);
	}
	if ((*ptr2)->previous && ((*ptr2)->previous->key == INFILE
			|| (*ptr2)->previous->key == OUTFILE))
	{
		(*ptr2)->value = ft_strjoin((*ptr2)->previous->value, (*ptr2)->value,
				1);
		ft_del_page(dic, (*ptr2)->previous);
	}
	if (operation == LESSER)
		(*ptr2)->key = INFILE;
	else
		(*ptr2)->key = OUTFILE;
}

void	ft_op_quotes(t_dic **dic, t_dic **ptr2, int operation)
{
	if ((*ptr2)->previous && ((*ptr2)->previous->key == INFILE
			|| (*ptr2)->previous->key == OUTFILE))
	{
		(*ptr2)->next->value = ft_strjoin((*ptr2)->previous->value,
				(*ptr2)->next->value, 1);
		*ptr2 = (*ptr2)->next;
		ft_del_page(dic, (*ptr2)->previous->previous);
		ft_del_page(dic, (*ptr2)->previous);
		ft_del_page(dic, (*ptr2)->next);
	}
	else if ((*ptr2)->key == DQUOTE || (*ptr2)->key == SQUOTE)
	{
		*ptr2 = (*ptr2)->next;
		ft_del_page(dic, (*ptr2)->previous);
		ft_del_page(dic, (*ptr2)->next);
	}
	if (operation == LESSER)
		(*ptr2)->key = INFILE;
	else
		(*ptr2)->key = OUTFILE;
}

void	ft_less_great(t_dic **dic, t_dic *ptr1, int operation)
{
	t_dic	*ptr2;

	ptr2 = ptr1->next;
	if (ptr2)
	{
		ft_pre_less_great(dic, &ptr2);
		if (ptr2 && ptr2->key == operation)
			ft_op_less_great(dic, &ptr2, &ptr1, operation);
		else if (ptr2 && (ptr2->key == CMD || ptr2->key == DOLLAR
				|| ptr2->key == DQUOTE || ptr2->key == SQUOTE))
		{
			ft_op_dquote(&ptr2);
			while (ptr2 && (ptr2->key == CMD || ptr2->key == DOLLAR
					|| ptr2->key == DQUOTE || ptr2->key == SQUOTE))
			{
				ft_op_quotes(dic, &ptr2, operation);
				ptr2 = ptr2->next;
			}
		}
		else
			g_glob.exit_status = SYNTAX_ERROR;
	}
	else
		g_glob.exit_status = SYNTAX_ERROR;
}
