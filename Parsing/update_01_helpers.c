/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_01_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 01:27:29 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/07 23:18:11 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_update_01_in_out_core(t_dic **ptr, char *var, t_iterators *itr)
{
	printf("{%s}\n", (*ptr)->next->value);
	if ((*ptr)->next->value[itr->i + itr->j + 1] == '?')
		(*ptr)->next->value = ft_replace_str((*ptr)->next->value,
				ft_expand("?\0"), itr->i, itr->i + 1);
	else
	{
		while ((*ptr)->next->value[itr->i + itr->j + 1]
			&& ft_is_delimiter((*ptr)->next->value[itr->i + itr->j + 1])
			!= SPACES && ft_is_delimiter((*ptr)->next->value[itr->i
					+ itr->j + 1]) != DQUOTE)
			itr->j++;
		var = ft_substr((*ptr)->next->value, itr->i + 1, itr->j, 1);
		(*ptr)->next->value = ft_replace_str((*ptr)->next->value,
				ft_expand(var), itr->i, itr->i + itr->j);
	}
}

void	ft_update_01_in_out(t_dic **ptr, char *var, t_iterators *itr)
{
	itr->i = 0;
	if ((*ptr)->next)
	{
		while ((*ptr)->next->value[itr->i])
		{
			itr->j = 0;
			if ((*ptr)->next->value[itr->i] == '$' && (*ptr)->next->value[itr->i
					+ itr->j + 1])
				ft_update_01_in_out_core(ptr, var, itr);
			if (itr->j != 0)
				itr->i += itr->j;
			else
				itr->i++;
		}
	}
}

void	ft_update_01_dquote_core(t_dic **ptr, char *var, t_iterators *itr)
{
	if ((*ptr)->next->value[itr->i + itr->j + 1] == '?')
		(*ptr)->next->value = ft_replace_str((*ptr)->next->value,
				ft_expand("?\0"), itr->i, itr->i + 1);
	else if (ft_isdigit((*ptr)->next->value[itr->i + itr->j + 1]))
		(*ptr)->next->value = ft_replace_str((*ptr)->next->value,
				"", itr->i, itr->i + 1);
	else
	{
		while ((*ptr)->next->value[itr->i + itr->j + 1]
			&& ft_is_delimiter((*ptr)->next->value[itr->i + itr->j
					+ 1]) != SPACES && (*ptr)->next->value[itr->i + itr->j
				+ 1] != '\"' && (*ptr)->next->value[itr->i + itr->j + 1] != '\''
			&& (*ptr)->next->value[itr->i + itr->j + 1] != '$'
			&& (*ptr)->next->value[itr->i + itr->j + 1] != '<'
			&& (*ptr)->next->value[itr->i + itr->j + 1] != '>')
			itr->j++;
		var = ft_substr((*ptr)->next->value, itr->i + 1, itr->j, 1);
		(*ptr)->next->value = ft_replace_str((*ptr)->next->value,
				ft_expand(var), itr->i, itr->i + itr->j);
	}
}

void	ft_update_01_dquote(t_dic **ptr, char *var, t_iterators *itr)
{
	itr->i = 0;
	if ((*ptr)->next && (*ptr)->next->key == CMD)
	{
		while ((*ptr)->next->value && (*ptr)->next->value[itr->i])
		{
			itr->j = 0;
			if ((*ptr)->next->value[itr->i] == '$' && (*ptr)->next->value[itr->i
					+ 1] && (*ptr)->next->value[itr->i + 1] != '$')
			{
				ft_update_01_dquote_core(ptr, var, itr);
				continue ;
			}
			itr->i++;
		}
		*ptr = (*ptr)->next;
	}
}
