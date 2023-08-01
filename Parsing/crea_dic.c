/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crea_dic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 06:26:52 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/01 06:27:16 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_nodelquo(t_dic **dic, char *input, t_iterators *itr, int *pipe)
{
	itr->j = 0;
	if (input[itr->i + itr->j] && !ft_is_delimiter(input[itr->i + itr->j]))
	{
		while (input[itr->i + itr->j] && !ft_is_delimiter(input[itr->i + itr->j]))
			itr->j++;
		ft_addpage_back(dic, ft_pagenew(CMD, ft_substr(input, itr->i, itr->j, 1),
					*pipe));
		itr->j--;
	}
	return (itr->j);
}

int	ft_delimiter_v00(t_dic **dic, char *input, t_iterators *itr, int *pipe)
{
	itr->j = 0;
	if (input[itr->i] && (ft_is_delimiter(input[itr->i]) == SQUOTE
			|| ft_is_delimiter(input[itr->i]) == DQUOTE))
		ft_squote_dquote(dic, input, *pipe, itr->i);
	else if (input[itr->i] && ft_is_delimiter(input[itr->i]) == DOLLAR)
	{
		itr->j = ft_dollar(dic, input, *pipe, itr->i);
		if (itr->j == -1)
			itr->i++;
	}
	else if (input[itr->i] && ft_is_delimiter(input[itr->i]) == SPACE)
		ft_addpage_back(dic, ft_pagenew(SPACE, " ", *pipe));
	else if (input[itr->i] && ft_is_delimiter(input[itr->i]) == GREATER)
		ft_addpage_back(dic, ft_pagenew(GREATER, ">\0", *pipe));
	else if (input[itr->i] && ft_is_delimiter(input[itr->i]) == PIPE)
		ft_addpage_back(dic, ft_pagenew(PIPE, "|\0", (*pipe)++));
	return (itr->j);
}

int	ft_delimiter_v01(t_dic **dic, char *input, t_iterators *itr, int *pipe)
{
	int	l;

	if (input[itr->i] && ft_is_delimiter(input[itr->i]) == LESSER)
	{
		ft_addpage_back(dic, ft_pagenew(LESSER, "<\0", *pipe));
		l = ft_get_limiter(dic, input, itr->i, *pipe);
		if (l == -1)
		{
			itr->i++;
			return (0);
		}
		itr->i = --l;
	}
	return (1);
}

int	ft_del_no_del(t_dic **dic, char *input, t_iterators *itr, int *pipe)
{
	if (input[itr->i + itr->j] && !ft_is_delimiter(input[itr->i + itr->j]))
	{
		itr->j = ft_nodelquo(dic, input, itr, pipe);
		if (itr->j == -2)
			return (-2);
	}
	else if (input[itr->i + itr->j] && ft_is_delimiter(input[itr->i + itr->j]))
	{
		itr->j = ft_delimiter_v00(dic, input, itr, pipe);
		if (itr->j == -1)
			return (-1);
		else if (itr->j == -2)
			return (-2);
		if (!ft_delimiter_v01(dic, input, itr, pipe))
			return (-1);
	}
	return(1);
}

t_dic	*ft_crea_dic(char *input)
{
	t_rand	var;

	var.itr = ft_init_cre(&var.dic, input, &var.pipe);
	if (!var.itr)
		return(NULL);
	while (input[var.itr->i])
	{
		var.itr->j = 0;
		if (input[var.itr->i + var.itr->j] && g_glob.open == 1)
		{
			var.itr->j = ft_open_quotes(&var.dic, input, var.pipe, var.itr->i);
			if (var.itr->j == -1)
				break ;
		}
		else
		{
			var.UwU = ft_del_no_del(&var.dic, input, var.itr, &var.pipe);
			if (var.UwU == -1)
				continue;
			else if (var.UwU == -2)
				break;
		}
		var.itr->i += var.itr->j + 1;
	}
	return (var.dic);
}
