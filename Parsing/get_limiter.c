/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_limiter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 02:57:07 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/07 17:54:35 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_get_lim_core_sq(char *input, char **val, int *i, t_iterators *itr)
{
	itr->l++;
	while (input[*i + itr->j + itr->k + itr->l]
		&& input[*i + itr->j + itr->k + itr->l] != '\'')
		itr->l++;
	if (!input[*i + itr->j + itr->k + itr->l])
	{
		g_glob.exit_status = SYNTAX_ERROR;
		return ;
	}
	*val = ft_strjoin(*val, ft_substr(input, *i + itr->j + itr->k + 1,
				itr->l - 1, 1), 1);
	itr->k += itr->l;
}

void	ft_get_lim_core_dq(char *input, char **val, int *i, t_iterators *itr)
{
	itr->l++;
	while (input[*i + itr->j + itr->k + itr->l]
		&& input[*i + itr->j + itr->k + itr->l] != '\"')
		itr->l++;
	if (!input[*i + itr->j + itr->k + itr->l])
	{
		g_glob.exit_status = SYNTAX_ERROR;
		return ;
	}
	*val = ft_strjoin(*val, ft_substr(input, *i + itr->j + itr->k + 1,
				itr->l - 1, 1), 1);
	itr->k += itr->l;
}

void	ft_get_limiter_core(char *input, char **val, int *i, t_iterators *itr)
{
	itr->l = 0;
	if (input[*i + itr->j + itr->k + itr->l] == '\'')
		ft_get_lim_core_sq(input, val, i, itr);
	else if (input[*i + itr->j + itr->k + itr->l] == '\"')
		ft_get_lim_core_dq(input, val, i, itr);
	else
		*val = ft_strjoin(*val, ft_substr(input, *i + itr->j + itr->k, 1, 1),
				1);
	itr->k++;
}

int	ft_get_limiter(t_dic **dic, char *input, int i, int pipe)
{
	t_iterators	itr;
	char		*val;

	itr.j = 1;
	itr.k = 0;
	if (input[i + itr.j] && input[i + itr.j] == '<')
	{
		ft_addpage_back(dic, ft_pagenew(LESSER, "<\0", pipe));
		itr.j++;
		while (input[i + itr.j] && ft_is_delimiter(input[i + itr.j]) == SPACES)
			itr.j++;
		if (!input[i + itr.j] || input[i + itr.j] == '<'
			|| input[i + itr.j] == '>' || input[i + itr.j] == '|')
			return (-1);
		val = NULL;
		while (input[i + itr.j + itr.k] && input[i + itr.j + itr.k] != '<'
			&& ft_is_delimiter(input[i + itr.j + itr.k]) != SPACES && input[i
				+ itr.j + itr.k] != '>' && input[i + itr.j + itr.k] != '|')
			ft_get_limiter_core(input, &val, &i, &itr);
		ft_addpage_back(dic, ft_pagenew(LIMITER, val, pipe));
		return (i + itr.j + itr.k);
	}
	else
		return (-1);
	return (i);
}
