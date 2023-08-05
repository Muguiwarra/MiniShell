/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_dic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 03:15:24 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/05 03:08:04 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_update_00(t_dic **dic)
{
	t_dic	*ptr1;

	ft_rm_multi_sp(dic);
	ptr1 = *dic;
	while (ptr1)
	{
		if (ptr1->key == LESSER)
		{
			if (ptr1->next && ptr1->next->key == GREATER)
				ft_del_page(dic, ptr1->next);
			ft_less_great(dic, ptr1, LESSER);
		}
		else if (ptr1->key == GREATER)
			ft_less_great(dic, ptr1, GREATER);
		else if (ptr1->key == PIPE)
		{
			if (!ptr1->next || !ptr1->previous)
				g_glob.exit_status = SYNTAX_ERROR;
		}
		ptr1 = ptr1->next;
	}
}

void	ft_update_01(t_dic **dic)
{
	char		*var;
	t_dic		*ptr;
	t_iterators	itr;

	ptr = *dic;
	var = NULL;
	while (ptr)
	{
		if (ptr->key == INFILE || ptr->key == OUTFILE)
			ft_update_01_in_out(&ptr, var, &itr);
		else if (ptr->key == DQUOTE)
			ft_update_01_dquote(&ptr, var, &itr);
		ptr = ptr->next;
	}
}

void	ft_update_02(t_dic **dic)
{
	t_dic	*ptr;

	ptr = *dic;
	ft_pre_update_02(dic, &ptr);
	while (ptr)
	{
		if (ptr->key == DQUOTE || ptr->key == SQUOTE)
		{
			ft_update_02_quotes(dic, &ptr);
			continue;
		}
		else if (ptr->key == DOLLAR && ptr->previous
				&& ptr->previous->key == CMD)
			ft_update_02_dolcmd(dic, &ptr);
		else if (ptr->key == CMD && ptr->previous && ptr->previous->key == CMD)
		{
			ptr->value = ft_strjoin(ptr->previous->value, ptr->value, 1);
			ft_del_page(dic, ptr->previous);
			ptr = ptr->next;
			continue;
		}
		ptr = ptr->next;
	}
}

void	ft_update_03(t_dic **dic)
{
	t_dic	*ptr;

	ptr = *dic;
	if (ptr->key == SPACE || ptr->key == DQUOTE || ptr->key == SQUOTE
		|| ptr->key == DOLLAR || ptr->key == LESSER || ptr->key == GREATER
		|| ptr->key == APPEND)
	{
		if (ptr->key == DQUOTE || ptr->key == SQUOTE || ptr->key == APPEND)
			ptr->next->special = ptr->key;
		ft_del_page(dic, ptr);
	}
	ptr = *dic;
	while (ptr)
	{
		if (ptr->key == SPACE || ptr->key == DQUOTE || ptr->key == SQUOTE
			|| ptr->key == DOLLAR || ptr->key == LESSER || ptr->key == GREATER
			|| ptr->key == APPEND)
		{
			if (ptr->key == DQUOTE || ptr->key == SQUOTE || ptr->key == APPEND)
				if (ptr->next)
					ptr->next->special = ptr->key;
			ft_del_page(dic, ptr);
		}
		ptr = ptr->next;
	}
}

char	*ft_replace_str(char *original, char *new, int start, int end)
{
	char	*result;
	t_iterators itr;

	itr.i = 0;
	itr.j = 0;
	itr.ln = ft_strlen(new);
	itr.lo = ft_strlen(original);
	result = ft_malloc(itr.lo - end + start + itr.ln + 2, 1);
	while (original[itr.i])
	{
		if (itr.i != start)
			result[itr.j++] = original[itr.i++];
		else
		{
			if (itr.ln != 0)
			{
				itr.k = 0;
				while (new[itr.k])
					result[itr.j++] = new[itr.k++];
			}
			itr.i = end + 1;
		}
	}
	result[itr.j] = '\0';
	return (result);
}
