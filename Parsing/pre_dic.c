/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_dic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 03:13:13 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/07 23:52:36 by nabboune         ###   ########.fr       */
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
	int	j;
	int	k;

	j = 0;
	k = 1;
	if ((input[i + 1] && ft_is_delimiter(input[i + 1])) || !input[i + 1])
	{
		if (!input[i + 1] || ft_is_delimiter(input[i + 1]) == SPACES)
			ft_addpage_back(dic, ft_pagenew(CMD, "$\0", pipe));
		else if (ft_is_delimiter(input[i + 1]) == DQUOTE
			|| ft_is_delimiter(input[i + 1]) == SQUOTE)
			return (-1);
		else
			return (ft_syntax_err(), -2);
	}
	else if (input[i + 1] && !ft_is_delimiter(input[i + 1]))
	{
		if (!ft_isdigit(input[i + j + 1]))
		{
			while (input[i + j + 1] && !ft_is_delimiter(input[i + j + 1]))
				j++;
			ft_addpage_back(dic, ft_pagenew(DOLLAR, "$\0", pipe));
			ft_addpage_back(dic, ft_pagenew(CMD,
					ft_expand(ft_substr(input, i + 1, j, 1)), pipe));
		}
		else
		{
			ft_addpage_back(dic, ft_pagenew(DOLLAR, "$\0", pipe));
			ft_addpage_back(dic, ft_pagenew(CMD,
					ft_expand(ft_substr(input, i + 1, ++j, 1)), pipe));
		}
	}
	return (j);
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
