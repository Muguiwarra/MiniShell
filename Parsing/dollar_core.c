/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 04:36:23 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/08 04:36:49 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_dollar_triple_core(t_dic **dic, char *input,
			int pipe, t_iterators *itr)
{
	itr->l = 0;
	if (!ft_isdigit(input[itr->i + itr->j + itr->l + 1]))
	{
		while (input[itr->i + itr->j + itr->l + 1]
			&& (ft_isalnum(input[itr->i + itr->j + itr->l + 1])
				|| input[itr->i + itr->j + itr->l + 1] == '_'))
			itr->l++;
		ft_addpage_back(dic, ft_pagenew(DOLLAR, "$\0", pipe));
		ft_addpage_back(dic, ft_pagenew(CMD,
				ft_expand(ft_substr(input, itr->i + 1,
						itr->j + itr->l, 1)), pipe));
	}
	else
	{
		ft_addpage_back(dic, ft_pagenew(DOLLAR, "$\0", pipe));
		ft_addpage_back(dic, ft_pagenew(CMD,
				ft_expand(ft_substr(input, itr->i + 1, ++itr->j, 1)), pipe));
	}
	itr->j += itr->l;
}

void	ft_dollar_double_core(t_dic **dic, char *input,
			int pipe, t_iterators *itr)
{
	if (input[itr->i + itr->j + 1] == '?')
	{
		ft_addpage_back(dic, ft_pagenew(DOLLAR, "$\0", pipe));
		ft_addpage_back(dic, ft_pagenew(CMD,
				ft_expand("?\0"), pipe));
		itr->j++;
	}
	else
		ft_dollar_triple_core(dic, input, pipe, itr);
}

int	ft_dollar_core(t_dic **dic, char *input, int pipe, t_iterators *itr)
{
	if ((input[itr->i + itr->j + 1]
			&& ft_is_delimiter(input[itr->i + itr->j + 1]))
		|| !input[itr->i + itr->j + 1])
	{
		if (!input[itr->i + itr->j + 1]
			|| ft_is_delimiter(input[itr->i + itr->j + 1]) == SPACES)
			ft_addpage_back(dic, ft_pagenew(CMD, "$\0", pipe));
		else if (ft_is_delimiter(input[itr->i + itr->j + 1]) == DQUOTE
			|| ft_is_delimiter(input[itr->i + itr->j + 1]) == SQUOTE)
			return (-1);
		else
			return (ft_syntax_err(), -2);
	}
	else if (input[itr->i + itr->j + 1]
		&& !ft_is_delimiter(input[itr->i + itr->j + 1]))
		ft_dollar_double_core(dic, input, pipe, itr);
	return (0);
}

void	ft_dollar_init_itr(t_iterators *itr, int i)
{
	itr->i = i;
	itr->j = 0;
	itr->k = 1;
}
