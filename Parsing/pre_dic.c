/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_dic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 03:13:13 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/08 04:36:06 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_syntax_err(void)
{
	g_glob.exit_status = SYNTAX_ERROR;
}

int	ft_open_quotes(t_dic **dic, char *input, int pipe, int i)
{
	int		j;
	t_dic	*last_page;

	j = 0;
	last_page = ft_lastpage(*dic);
	while (input[i + j] && input[i + j] != last_page->value[0])
		j++;
	if (!input[i + j])
	{
		g_glob.exit_status = SYNTAX_ERROR;
		return (-1);
	}
	ft_addpage_back(dic, ft_pagenew(CMD, ft_substr(input, i, j, 1), pipe));
	ft_addpage_back(dic, ft_pagenew(last_page->key, last_page->value, pipe));
	g_glob.open = 0;
	return (j);
}

void	ft_squote_dquote(t_dic **dic, char *input, int pipe, int i)
{
	if (input[i] && ft_is_delimiter(input[i]) == SQUOTE)
	{
		if (g_glob.open == 0)
			g_glob.open = 1;
		else
			g_glob.open = 0;
		ft_addpage_back(dic, ft_pagenew(SQUOTE, "\'\0", pipe));
	}
	else if (input[i] && ft_is_delimiter(input[i]) == DQUOTE)
	{
		if (g_glob.open == 0)
			g_glob.open = 1;
		else
			g_glob.open = 0;
		ft_addpage_back(dic, ft_pagenew(DQUOTE, "\"\0", pipe));
	}
}

int	ft_dollar(t_dic **dic, char *input, int pipe, int i)
{
	int			ret;
	t_iterators	itr;

	ft_dollar_init_itr(&itr, i);
	if (input[itr.i + itr.j + 1] && input[itr.i + itr.j + 1] == '$')
	{
		while (input[itr.i + itr.j + 1] && input[itr.i + itr.j + 1] == '$')
			itr.j++;
		if (input[itr.i + itr.j + 1]
			&& !ft_is_delimiter(input[itr.i + itr.j + 1]))
		{
			ft_addpage_back(dic, ft_pagenew(CMD,
					ft_substr(input, itr.i, itr.j - 1, 1), pipe));
			itr.j--;
		}
		ft_addpage_back(dic, ft_pagenew(CMD,
				ft_substr(input, itr.i, itr.j + 1, 1), pipe));
	}
	else
	{
		ret = ft_dollar_core(dic, input, pipe, &itr);
		if (ret == -1 || ret == -2)
			return (ret);
	}
	return (itr.j);
}

t_iterators	*ft_init_cre(t_dic **dic, char *input, int *pipe)
{
	t_iterators	*itr;

	itr = ft_malloc(sizeof(t_iterators), 1);
	if (!itr)
		return (0);
	itr->i = 0;
	g_glob.open = 0;
	*pipe = 0;
	*dic = NULL;
	while (input[itr->i] && ft_is_delimiter(input[itr->i]) == SPACES)
		itr->i++;
	if (!input[itr->i])
		return (0);
	return (itr);
}
