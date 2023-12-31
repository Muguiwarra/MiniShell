/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:06:51 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/08 04:23:33 by nabboune         ###   ########.fr       */
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

void	ft_check_pipes(t_dic **dic)
{
	if ((*dic)->next)
		(*dic) = (*dic)->next;
	while ((*dic) && (*dic)->key == SPACES)
		(*dic) = (*dic)->next;
	if ((*dic)->key == PIPE)
		g_glob.exit_status = SYNTAX_ERROR;
}

void	ft_check_operation(t_dic **dic)
{
	(*dic) = (*dic)->next;
	if ((*dic) && (*dic)->key == SPACES)
	{
		while ((*dic) && (*dic)->key == SPACES)
			(*dic) = (*dic)->next;
		if ((*dic) && ((*dic)->key == LESSER || (*dic)->key == GREATER))
			g_glob.exit_status = SYNTAX_ERROR;
	}
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
			ft_check_operation(&dic);
		else if (dic->key == PIPE)
			ft_check_pipes(&dic);
		else if (dic->key == HEREDOC)
			if (++itr.doc == 17)
				g_glob.exit_status = MAXIMUM_HEREDOC;
		if (dic)
			dic = dic->next;
	}
}

void	ft_file_err(t_dic *dic)
{
	ft_dprintf(2, "Minishell-0.1: %s: %s\n", dic->value, strerror(errno));
	g_glob.exit_status = UNSPECIFIED_ERROR;
}
