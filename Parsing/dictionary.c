/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 03:53:58 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/01 19:30:11 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			echo ""hi ==> " hi"
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

void	ft_pre_less_great(t_dic **dic, t_dic **ptr2)
{
	while (*ptr2 && (*ptr2)->key == SPACE)
		*ptr2 = (*ptr2)->next;
	if (*ptr2 && (*ptr2)->key == DOLLAR)
	{
		if ((*ptr2)->next)
		{
			*ptr2 = (*ptr2)->next;
			ft_del_page(dic, (*ptr2)->previous);
		}
	}
}

void	ft_limiter_outfile(t_dic **ptr2, int operation)
{
	if (operation == LESSER)
		(*ptr2)->key = LIMITER;
	else
		(*ptr2)->key = OUTFILE;
}

void	ft_del_move(t_dic **dic, t_dic **ptr2)
{
	ft_del_page(dic, *ptr2);
	*ptr2 = (*ptr2)->next;
}

void	ft_op_less_great(t_dic **dic, t_dic **ptr2, t_dic **ptr1, int operation)
{
	while ((*ptr2)->next && (*ptr2)->next->key == SPACE)
		ft_del_move(dic, ptr2);
	if ((*ptr2)->next && (*ptr2)->next->key != LESSER
		&& (*ptr2)->next->key != GREATER)
	{
		if ((*ptr2)->next->key == DQUOTE || (*ptr2)->next->key == SQUOTE)
		{
			ft_del_page(dic, (*ptr2)->next);
			ft_del_page(dic, (*ptr2)->next->next);
		}
		ft_del_page(dic, *ptr2);
		if (operation == LESSER)
			(*ptr1)->key = HEREDOC;
		else
			(*ptr1)->key = APPEND;
		*ptr2 = (*ptr1)->next;
		if (*ptr2)
			ft_limiter_outfile(ptr2, operation);
		else
			g_glob.exit_status = SYNTAX_ERROR;
	}
	else
		g_glob.exit_status = SYNTAX_ERROR;
}

int		ft_op_dquote_cond(t_dic **ptr2, int i, int j)
{
	if ((*ptr2)->next->value[i + j + 1]
		&& ft_is_delimiter((*ptr2)->next->value[i + j
			+ 1]) != SPACE
		&& ft_is_delimiter((*ptr2)->next->value[i + j
			+ 1]) != DQUOTE)
		return (1);
	return (0);
}

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
				if (ptr2 && (ptr2->key == CMD || ptr2->key == DOLLAR))
				{
					if (ptr2->key == DOLLAR)
					{
						ptr2 = ptr2->next;
						ft_del_page(dic, ptr2->previous);
					}
					if (ptr2->previous && (ptr2->previous->key == INFILE
							|| ptr2->previous->key == OUTFILE))
					{
						ptr2->value = ft_strjoin(ptr2->previous->value,
													ptr2->value,
													1);
						ft_del_page(dic, ptr2->previous);
					}
					if (operation == LESSER)
						ptr2->key = INFILE;
					else
						ptr2->key = OUTFILE;
				}
				else if (ptr2 && (ptr2->key == DQUOTE || ptr2->key == SQUOTE))
				{
					if (ptr2->previous && (ptr2->previous->key == INFILE
							|| ptr2->previous->key == OUTFILE))
					{
						ptr2->next->value = ft_strjoin(ptr2->previous->value,
														ptr2->next->value,
														1);
						ptr2 = ptr2->next;
						ft_del_page(dic, ptr2->previous->previous);
						ft_del_page(dic, ptr2->previous);
						ft_del_page(dic, ptr2->next);
					}
					else
					{
						ptr2 = ptr2->next;
						ft_del_page(dic, ptr2->previous);
						ft_del_page(dic, ptr2->next);
					}
					if (operation == LESSER)
						ptr2->key = INFILE;
					else
						ptr2->key = OUTFILE;
				}
				ptr2 = ptr2->next;
			}
		}
		else
			g_glob.exit_status = SYNTAX_ERROR;
	}
	else
		g_glob.exit_status = SYNTAX_ERROR;
}

void	ft_update_02(t_dic **dic)
{
	t_dic	*ptr;

	ptr = *dic;
	if (ptr->key == DQUOTE || ptr->key == SQUOTE)
	{
		ptr->next->special = ptr->key;
		ptr = ptr->next;
		ft_del_page(dic, ptr->previous);
		ft_del_page(dic, ptr->next);
		if (ptr->next && ptr->next->key == CMD)
		{
			ptr->next->value = ft_strjoin(ptr->value, ptr->next->value, 1);
			ptr = ptr->next;
			ft_del_page(dic, ptr->previous);
		}
		else if (ptr->next && (ptr->next->key == DQUOTE
					|| ptr->next->key == SQUOTE))
		{
			ptr->next->next->value = ft_strjoin(ptr->value,
												ptr->next->next->value,
												1);
			ptr = ptr->next->next;
			ft_del_page(dic, ptr->previous->previous);
			ft_del_page(dic, ptr->previous);
			ft_del_page(dic, ptr->next);
		}
		while (ptr->next && ptr->next->key == CMD)
		{
			ptr->next->value = ft_strjoin(ptr->value, ptr->next->value, 1);
			ptr = ptr->next;
			ft_del_page(dic, ptr->previous);
		}
		while (ptr->next && ptr->next->key == DOLLAR)
		{
			ptr->next->next->value = ft_strjoin(ptr->value,
												ptr->next->next->value,
												1);
			ptr = ptr->next->next;
			ft_del_page(dic, ptr->previous->previous);
			ft_del_page(dic, ptr->previous);
		}
		while (ptr->next && (ptr->next->key == DQUOTE
				|| ptr->next->key == SQUOTE))
		{
			ptr->next->next->value = ft_strjoin(ptr->value,
												ptr->next->next->value,
												1);
			ptr = ptr->next->next;
			ft_del_page(dic, ptr->previous->previous);
			ft_del_page(dic, ptr->previous);
			ft_del_page(dic, ptr->next);
		}
	}
	while (ptr)
	{
		if (ptr->key == DQUOTE || ptr->key == SQUOTE)
		{
			if (ptr->previous && ptr->previous->key == CMD)
				ptr->next->value = ft_strjoin(ptr->previous->value,
												ptr->next->value,
												1);
			ptr = ptr->next;
			ft_del_page(dic, ptr->previous->previous);
			ft_del_page(dic, ptr->previous);
			ft_del_page(dic, ptr->next);
			continue ;
		}
		else if (ptr->key == DOLLAR && ptr->previous
				&& ptr->previous->key == CMD)
		{
			ptr->next->value = ft_strjoin(ptr->previous->value,
											ptr->next->value,
											1);
			ptr = ptr->next;
			ft_del_page(dic, ptr->previous->previous);
			ft_del_page(dic, ptr->previous);
		}
		ptr = ptr->next;
	}
}

void	ft_update_01(t_dic **dic)
{
	t_dic	*ptr;
	char	*var;
	int		i;
	int		j;

	ptr = *dic;
	while (ptr)
	{
		if (ptr->key == INFILE || ptr->key == OUTFILE)
		{
			i = 0;
			if (ptr->next)
			{
				while (ptr->next->value[i])
				{
					j = 0;
					if (ptr->next->value[i] == '$' && ptr->next->value[i + j
						+ 1])
					{
						if (ptr->next->value[i + j + 1] == '?')
							ptr->next->value = ft_replace_str(ptr->next->value,
																ft_expand("?\0"),
																i,
																i + 1);
						else
						{
							while (ptr->next->value[i + j + 1]
								&& ft_is_delimiter(ptr->next->value[i + j
									+ 1]) != SPACE
								&& ft_is_delimiter(ptr->next->value[i + j
									+ 1]) != DQUOTE)
								j++;
							var = ft_substr(ptr->next->value, i + 1, j, 1);
							ptr->next->value = ft_replace_str(ptr->next->value,
																ft_expand(var),
																i,
																i + j);
						}
					}
					if (j != 0)
						i += j;
					else
						i++;
				}
			}
		}
		else if (ptr->key == DQUOTE)
		{
			i = 0;
			if (ptr->next && ptr->next->key == CMD)
			{
				while (ptr->next->value && ptr->next->value[i])
				{
					j = 0;
					if (ptr->next->value[i] == '$' && ptr->next->value[i + 1]
						&& ptr->next->value[i + 1] != '$')
					{
						if (ptr->next->value[i + j + 1] == '?')
							ptr->next->value = ft_replace_str(ptr->next->value,
																ft_expand("?\0"),
																i,
																i + 1);
						else
						{
							while (ptr->next->value[i + j + 1]
								&& ft_is_delimiter(ptr->next->value[i + j
									+ 1]) != SPACE && ptr->next->value[i + j
								+ 1] != '\"' && ptr->next->value[i + j
								+ 1] != '\'' && ptr->next->value[i + j
								+ 1] != '$' && ptr->next->value[i + j
								+ 1] != '<' && ptr->next->value[i + j
								+ 1] != '>')
								j++;
							var = ft_substr(ptr->next->value, i + 1, j, 1);
							ptr->next->value = ft_replace_str(ptr->next->value,
																ft_expand(var),
																i,
																i + j);
						}
						continue ;
					}
					i++;
				}
				ptr = ptr->next;
			}
		}
		ptr = ptr->next;
	}
}

int	ft_get_limiter(t_dic **dic, char *input, int i, int pipe)
{
	int		j;
	int		k;
	int		l;
	char	*val;

	j = 1;
	k = 0;
	if (input[i + j] && input[i + j] == '<')
	{
		ft_addpage_back(dic, ft_pagenew(LESSER, "<\0", pipe));
		j++;
		while (input[i + j] && ft_is_delimiter(input[i + j]) == SPACE)
			j++;
		if (!input[i + j] || input[i + j] == '<' || input[i + j] == '>'
			|| input[i + j] == '|')
			return (-1);
		val = NULL;
		while (input[i + j + k] && ft_is_delimiter(input[i + j + k]) != SPACE
			&& input[i + j + k] != '>' && input[i + j + k] != '<' && input[i + j
			+ k] != '|')
		{
			l = 0;
			if (input[i + j + k + l] == '\'')
			{
				l++;
				while (input[i + j + k + l] && input[i + j + k + l] != '\'')
					l++;
				val = ft_strjoin(val, ft_substr(input, i + j + k + 1, l - 1, 1),
						1);
				k += l;
			}
			else if (input[i + j + k + l] == '\"')
			{
				l++;
				while (input[i + j + k + l] && input[i + j + k + l] != '\"')
					l++;
				val = ft_strjoin(val, ft_substr(input, i + j + k + 1, l - 1, 1),
						1);
				k += l;
			}
			else
				val = ft_strjoin(val, ft_substr(input, i + j + k, 1, 1), 1);
			k++;
		}
		ft_addpage_back(dic, ft_pagenew(LIMITER, val, pipe));
		i += j + k;
		return (i);
	}
	else
		return (-1);
	return (i);
}
