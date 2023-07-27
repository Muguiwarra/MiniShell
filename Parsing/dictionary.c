/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 03:53:58 by nabboune          #+#    #+#             */
/*   Updated: 2023/07/27 04:51:08 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (ft_is_delimiter(input[i + 1]) == SPACE)
			ft_addpage_back(dic, ft_pagenew(CMD, "$\0", pipe));
		else if (ft_is_delimiter(input[i + 1]) == DQUOTE || ft_is_delimiter(input[i + 1]) == SQUOTE)
			return (-1);
		else
		{
			g_glob.exit_status = SYNTAX_ERROR;
			return (-2);
		}
	}
	else if (input[i + 1] && !ft_is_delimiter(input[i + 1]))
	{
		while (input[i + j + 1] && !ft_is_delimiter(input[i + j + 1]))
			j++;
		ft_addpage_back(dic, ft_pagenew(DOLLAR, "$\0", pipe));
		ft_addpage_back(dic, ft_pagenew(CMD, ft_expand(ft_substr(input, i + 1, j, 1)), pipe));
	}
	return (j);
}

t_dic	*ft_crea_dic(char *input)
{
	int		i;
	int		j;
	int		pipe;
	t_dic	*dic;

	i = 0;
	g_glob.open = 0;
	pipe = 0;
	dic = NULL;
	while(input[i] && ft_is_delimiter(input[i]) == SPACE)
		i++;
	if (!input[i])
		return (NULL);
	while (input[i])
	{
		j = 0;
		if (input[i + j] && g_glob.open == 1)
		{
			j = ft_open_quotes(&dic, input, pipe, i);
			if (j == -1)
				break ;
		}
		else if (input[i + j] && !ft_is_delimiter(input[i + j]))
		{
			while (input[i + j] && !ft_is_delimiter(input[i + j]))
				j++;
			ft_addpage_back(&dic, ft_pagenew(CMD, ft_substr(input, i, j, 1), pipe));
			j--;
		}
		else if (input[i + j] && ft_is_delimiter(input[i + j]))
		{
			if (input[i] && (ft_is_delimiter(input[i]) == SQUOTE || ft_is_delimiter(input[i]) == DQUOTE))
				ft_squote_dquote(&dic, input, pipe, i);
			else if (input[i] && ft_is_delimiter(input[i]) == PIPE)
				ft_addpage_back(&dic, ft_pagenew(PIPE, "|\0", pipe++));
			else if (input[i] && ft_is_delimiter(input[i]) == DOLLAR)
			{
				j = ft_dollar(&dic, input, pipe, i);
				if (j == -1)
				{
					i++;
					continue;
				}
				else if (j == -2)
					break ;
			}
			else if (input[i] && ft_is_delimiter(input[i]) == SPACE)
				ft_addpage_back(&dic, ft_pagenew(SPACE, " ", pipe));
			else if (input[i] && ft_is_delimiter(input[i]) == LESSER)
				ft_addpage_back(&dic, ft_pagenew(LESSER, "<\0", pipe));
			else if (input[i] && ft_is_delimiter(input[i]) == GREATER)
				ft_addpage_back(&dic, ft_pagenew(GREATER, ">\0", pipe));
		}
		i += j + 1;
	}
	return(dic);
}

void	ft_update_00(t_dic **dic)
{
	t_dic	*ptr1;
	// char	*var;
	// int		i;
	// int		j;

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

void	ft_check_dic(t_dic *dic)
{
	int	i;
	int	doc;

	doc = 0;
	while (dic)
	{
		i = 0;
		if (dic->key == DQUOTE)
		{
			i++;
			// printf("$$\n");
			if (dic->next)
				dic = dic->next;
			else
				g_glob.exit_status = SYNTAX_ERROR;
			while (dic)
			{
				if (dic->key == DQUOTE)
				{
					i++;
					break ;
				}
				dic = dic->next;
			}
			if (i != 2)
				g_glob.exit_status = SYNTAX_ERROR;
		}
		else if (dic->key == SQUOTE)
		{
			i++;
			if (dic->next)
				dic = dic->next;
			else
				g_glob.exit_status = SYNTAX_ERROR;
			while (dic)
			{
				if (dic->key == SQUOTE)
				{
					i++;
					break ;
				}
				dic = dic->next;
			}
			if (i != 2)
				g_glob.exit_status = SYNTAX_ERROR;
		}
		else if (dic->key == HEREDOC)
		{
			doc++;
			if (doc == 17)
			{
				g_glob.exit_status = MAXIMUM_HEREDOC;
				break ;
			}
		}
		if (dic)
			dic = dic->next;
	}
}

void	ft_less_great(t_dic **dic, t_dic *ptr1, int operation)
{
	t_dic	*ptr2;

	ptr2 = ptr1->next;
	if (ptr2)
	{
		while (ptr2 && ptr2->key == SPACE)
			ptr2 = ptr2->next;

		if (ptr2 && ptr2->key == DOLLAR)
		{
			if (ptr2->next)
			{
				ptr2 = ptr2->next;
				ft_del_page(dic, ptr2->previous);
			}
		}
		if (ptr2 && (ptr2->key == CMD || ptr2->key == DOLLAR))
		{
			if (operation == LESSER)
				ptr2->key = INFILE;
			else
				ptr2->key = OUTFILE;
		}
		else if (ptr2 && (ptr2->key == DQUOTE || ptr2->key == SQUOTE))
		{
			if (operation == LESSER)
				ptr2->next->key = INFILE;
			else
				ptr2->next->key = OUTFILE;
		}
		else if (ptr2 && ptr2->key == operation)
		{
			while (ptr2->next && ptr2->next->key == SPACE)
			{
				ft_del_page(dic, ptr2);
				ptr2 = ptr2->next;
			}
			if (ptr2->next && ptr2->next->key != LESSER && ptr2->next->key != GREATER)
			{
				if (ptr2->next->key == DQUOTE || ptr2->next->key == SQUOTE)
				{
					ft_del_page(dic, ptr2->next);
					ft_del_page(dic, ptr2->next->next);
				}
				ft_del_page(dic, ptr2);
				if (operation == LESSER)
					ptr1->key = HEREDOC;
				else
					ptr1->key = APPEND;
				ptr2 = ptr1->next;
				if (ptr2)
				{
					if (operation == LESSER)
						ptr2->key = LIMITER;
					else
						ptr2->key = OUTFILE;
				}
				else
					g_glob.exit_status = SYNTAX_ERROR;
			}
			else
				g_glob.exit_status = SYNTAX_ERROR;
		}
		else
			g_glob.exit_status = SYNTAX_ERROR;
	}
	else
		g_glob.exit_status = SYNTAX_ERROR;
}

void	ft_new_update_dic(t_dic **dic)
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

void	ft_update_01(t_dic **dic)
{
	t_dic	*ptr;

	ptr = *dic;
	while (ptr)
	{
		if (ptr->key == DQUOTE || ptr->key == SQUOTE)
		{
			if (ptr->previous && ptr->previous->key == CMD)
			{
				ptr->next->value = ft_strjoin(ptr->previous->value, ptr->next->value, 1);
				ptr = ptr->next;
				// ft_del_page(dic, ptr->previous->previous);
				// ft_del_page(dic, ptr->previous);
				// ft_del_page(dic, ptr->next);
				continue;
			}
		}
		else if (ptr->key == CMD && ptr->next && ptr->next->key == CMD)
		{
			ptr->next->value = ft_strjoin(ptr->value, ptr->next->value, 1);
			ptr = ptr->next;
			// ft_del_page(dic, ptr->previous);
		}
		else if (ptr->key == CMD && ptr->next && ptr->next->key == DOLLAR)
		{
			ptr->next->next->value = ft_strjoin(ptr->value, ptr->next->next->value, 1);
			ptr = ptr->next->next;
			// ft_del_page(dic, ptr->previous->previous);
			// ft_del_page(dic, ptr->previous);
		}
		ptr = ptr->next;
	}
}

void	ft_update_02(t_dic **dic)
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
					if (ptr->next->value[i] == '$')
					{
						while (ptr->next->value[i + j + 1] && ft_is_delimiter(ptr->next->value[i + j + 1]) != SPACE
							&& ft_is_delimiter(ptr->next->value[i + j + 1]) != DQUOTE)
							j++;
						var  = ft_substr(ptr->next->value, i + 1, j, 1);
						ptr->next->value = ft_replace_str(ptr->next->value, ft_expand(var), i, i + j);
					}
					if (j != 0)
						i += j;
					else
						i++;
				}
			}
			printf("\n");
		}
		else if (ptr->key == DQUOTE)
		{
			i = 0;
			printf("*\n");
			if (ptr->next)
			{
				while (ptr->next->value[i])
				{
					j = 0;
					printf("*\n");
					if (ptr->next->value[i] == '$')
					{
						printf("*\n");
						while (ptr->next->value[i + j + 1] && ft_is_delimiter(ptr->next->value[i + j + 1]) != SPACE
							&& ft_is_delimiter(ptr->next->value[i + j + 1]) != DQUOTE)
							j++;
						printf("==>%d\n", j);
						var  = ft_substr(ptr->next->value, i + 1, j, 1);
						ptr->next->value = ft_replace_str(ptr->next->value, ft_expand(var), i, i + j);
						printf("{%s}\n", ptr->next->value);
					}
					if (j != 0)
						i += j;
					else
						i++;
				}
			}
			printf("\n");
			ptr = ptr->next;
		}
		ptr = ptr->next;
	}
}
