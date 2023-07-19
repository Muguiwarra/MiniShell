/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 03:53:58 by nabboune          #+#    #+#             */
/*   Updated: 2023/07/19 09:24:48 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_dic	*ft_crea_dic(char *input)
{
	int		i;
	int		j;
	int		open;
	t_dic	*last_page;
	t_dic	*dic;

	i = 0;
	open = 0;
	dic = NULL;
	while (input[i])
	{
		j = 0;
		if (input[i + j] && !ft_is_delimiter(input[i + j]))
		{
			if (open == 0)
			{
				while (input[i + j] && !ft_is_delimiter(input[i + j]))
					j++;
				ft_addpage_back(&dic, ft_pagenew(CMD, ft_substr(input, i, j)));
				j--;
			}
			else
			{
				last_page = ft_lastpage(dic);
				while (input[i + j] && input[i + j] != last_page->value[0])
					j++;
				if (!input[i + j])
				{
					g_glob.exit_status = SYNTAX_ERROR;
					break ;
				}
				ft_addpage_back(&dic, ft_pagenew(CMD, ft_substr(input, i, j)));
				j--;
			}
		}
		else if (input[i + j] && ft_is_delimiter(input[i + j]))
		{
			if (input[i] && ft_is_delimiter(input[i]) == SQUOTE)
			{
				if (open == 0)
					open = 1;
				else
					open = 0;
				ft_addpage_back(&dic, ft_pagenew(SQUOTE, "\'\0"));
			}
			else if (input[i] && ft_is_delimiter(input[i]) == DQUOTE)
			{
				if (open == 0)
					open = 1;
				else
					open = 0;
				ft_addpage_back(&dic, ft_pagenew(DQUOTE, "\"\0"));
			}
			else if (input[i] && ft_is_delimiter(input[i]) == SPACE)
				ft_addpage_back(&dic, ft_pagenew(SPACE, " "));
			else if (input[i] && ft_is_delimiter(input[i]) == LESSER)
				ft_addpage_back(&dic, ft_pagenew(LESSER, "<\0"));
			else if (input[i] && ft_is_delimiter(input[i]) == GREATER)
				ft_addpage_back(&dic, ft_pagenew(GREATER, ">\0"));
			else if (input[i] && ft_is_delimiter(input[i]) == PIPE)
				ft_addpage_back(&dic, ft_pagenew(PIPE, "|\0"));
			else if (input[i] && ft_is_delimiter(input[i]) == DOLLAR && !ft_is_delimiter(input[i + 1]))
			{
				// NEED TO CHECK ! why if multiple spaces are next to dollar
				// the spaces don't get removed after calling the fct ft_rm_sp() !!
				while (input[i + j + 1] && !ft_is_delimiter(input[i + j + 1]))
					j++;
				ft_addpage_back(&dic, ft_pagenew(DOLLAR, "$\0"));
				ft_addpage_back(&dic, ft_pagenew(VAR, ft_substr(input, i + 1, j)));
			}
		}
		i += j + 1;
	}
	return(dic);
}

void	ft_update_dic(t_dic **dic)
{
	int		i;
	t_dic	*ptr1;
	t_dic	*ptr2;
	t_dic	*ptr3;

	ft_rm_sp(dic, 1);
	ptr1 = *dic;
	i = 1;
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
			if (ptr1->next && ptr1->next->key != PIPE)
			{
				ptr2 = ptr1->previous;
				while (ptr2)
				{
					ptr2->pipe = i;
					ptr2 = ptr2->previous;
				}
			}
			else
				g_glob.exit_status = SYNTAX_ERROR;
		}
		i++;
		ptr1 = ptr1->next;
	}
	ptr1 = *dic;
	while (ptr1)
	{
		ptr3 = ptr1;
		while (ptr1 && (ptr1->key == CMD || ptr1->key == ARG
				|| ptr1->key == LESSER || ptr1->key == GREATER
				|| ptr1->key == INFILE || ptr1->key == OUTFILE))
		{
			ptr2 = ptr1->next;
			if (ptr2)
			{
				if (ptr2->key == CMD)
					ptr2->key = ARG;
			}
			ptr1 = ptr1->next;
		}
		if (ptr1 == ptr3)
			ptr1 = ptr1->next;
	}
}

void	ft_check_dic(t_dic *dic)
{
	int	i;
	int	doc;

	i = 0;
	doc = 0;
	while (dic)
	{
		if (dic->key == DQUOTE)
		{
			i++;
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
		i = 0;
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
		if (ptr2 && ptr2->key == CMD)
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
			if (ptr2->next && ptr2->next->key != CMD)
				g_glob.exit_status = SYNTAX_ERROR;
			else
			{
				ft_del_page(dic, ptr2);
				if (operation == LESSER)
					ptr1->key = HEREDOC;
				else
					ptr2->key = APPEND;
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
		}
		else
			g_glob.exit_status = SYNTAX_ERROR;
	}
	else
		g_glob.exit_status = SYNTAX_ERROR;
}
