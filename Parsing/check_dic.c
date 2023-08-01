/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:06:51 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/01 18:07:15 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_quotes(t_dic **dic, int *i)
{
	int	tquote;

	tquote = (*dic)->key;
	(*i)++;
	if ((*dic)->next)
		*dic = (*dic)->next;
	else
		g_glob.exit_status = SYNTAX_ERROR;
	while (*dic)
	{
		if ((*dic)->key == tquote)
		{
			(*i)++;
			break ;
		}
		*dic = (*dic)->next;
	}
	if (*i != 2)
		g_glob.exit_status = SYNTAX_ERROR;
}

void	ft_check_dic(t_dic *dic)
{
	t_iterators	itr;

	itr.doc = 0;
	while (dic)
	{
		itr.i = 0;
		if (dic->key == DQUOTE || dic->key == SQUOTE)
			ft_check_quotes(&dic, &itr.i);
		else if (dic->key == LESSER || dic->key == GREATER)
		{
			dic = dic->next;
			if (dic && dic->key == SPACE)
			{
				while (dic && dic->key == SPACE)
					dic = dic->next;
				if (dic && (dic->key == LESSER || dic->key == GREATER))
					g_glob.exit_status = SYNTAX_ERROR;
			}
		}
		else if (dic->key == HEREDOC)
			if (++itr.doc == 17)
				g_glob.exit_status = MAXIMUM_HEREDOC;
		if (dic)
			dic = dic->next;
	}
}
