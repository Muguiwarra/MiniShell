/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:23:30 by nabboune          #+#    #+#             */
/*   Updated: 2023/06/23 06:33:49 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_prompt()
{
	char	*input;
	t_dic	*dic;
	// t_parsing_output	*out;

	while (1)
	{
		g_glob.exit_status = 0;
		rl_on_new_line();
		input = readline("MiniShell-0.1$ ");

		// To REMOVE after
		if (ft_strncmp(input, "exit", 5) == 0)
			exit(0);
		// Remember to REMOVE IT !!!
		dic = ft_crea_dic(input);
		ft_check_dic(dic);
		if (ft_check_exit())
		{
			ft_ending_prompt(input);
			continue;
		}
		ft_update_dic(&dic);
		if (ft_check_exit())
		{
			ft_ending_prompt(input);
			continue;
		}
		while (dic)
		{
			printf("Present : %p\nKey : %d\nValue : %s\nNext : %p\nPrevious : %p\n\n", dic, dic->key, dic->value, dic->next, dic->previous);
			dic = dic->next;
		}
		ft_ending_prompt(input);
	}
}

t_parsing_output	*ft_parsing_output(t_dic *dic)
{
	t_parsing_output	*out;
	t_dic				*ptr;
	int					op;
	int					i;
	int					j;

	out = ft_malloc(sizeof(t_parsing_output));
	i = 2;
	ptr = dic;
	while (ptr && ptr->key != PIPE)
	{
		op = ft_open_infile(ptr);
		if (ft_check_exit())
			continue;
		ptr = ptr->next;
	}
	while(dic)
	{
		if (dic->key == CMD)
		{
			ptr = dic->next;
			while (ptr && ptr->key != PIPE)
			{
				if (ptr->key == ARG)
					i++;
				ptr = ptr->next;
			}
			out->cmd = ft_malloc(i * sizeof(char *));
			if (!out->cmd)
			{
				g_glob.exit_status = UNSPECIFIED_ERROR;
				break ;
			}
			j = 0;
			while (dic && dic->key != PIPE)
			{
				if (ptr->key == CMD || ptr->key == ARG)
				{
					out->cmd[j] = dic->value;
					j++;
				}
				dic = dic->next;
			}
			out->cmd[j] = NULL;
		}
		// Fill Out The Nodes with the Infile fd...
	}
	return (out);
}

int		ft_open_infile(t_dic *dic)
{
	int	op;

	op = 0;
	while (dic && dic->key != PIPE)
	{
		if (dic->key == INFILE)
		{
			op = open(dic->value, O_RDONLY, 0777);
			if (op == -1)
			{
				perror(dic->value);
				g_glob.exit_status = UNSPECIFIED_ERROR;
				break ;
			}
			if (close(op) == -1)
			{
				perror(dic->value);
				g_glob.exit_status = UNSPECIFIED_ERROR;
				break ;
			}
		}
		dic = dic->next;
	}
	return (op);
}

void	ft_ending_prompt(char *input)
{
	add_history(input);
	ft_collect_garbadge();
	free(input);
	g_glob.exit_stat = g_glob.exit_status;
}

int	ft_check_exit()
{
	if (g_glob.exit_status == UNSPECIFIED_ERROR)
	{
		ft_printf("minishell: Unspecified error !\n");
		return (1);
	}
	else if (g_glob.exit_status == CMD_NOT_EXECUTABLE)
	{
		ft_printf("minishell: Command not executable !\n");
		return (1);
	}
	else if (g_glob.exit_status == CMD_NOT_FOUND)
	{
		ft_printf("minishell: Command not found !\n");
		return (1);
	}
	else if (g_glob.exit_status == SYNTAX_ERROR)
	{
		ft_printf("minishell: Syntax ERROR !\n");
		return (1);
	}
	return (0);
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

void	ft_update_dic(t_dic **dic)
{
	int		i;
	t_dic	*ptr1;
	t_dic	*ptr2;
	t_dic	*ptr3;

	ptr1 = *dic;
	i = 1;
	while (ptr1)
	{
		if (ptr1->key == LESSER)
		{
			if (ptr1->next)
			{
				ptr2 = ptr1->next;
				if (ptr2 && ptr2->key == CMD)
					ptr2->key = INFILE;
				else if (ptr2 && (ptr2->key == DQUOTE || ptr2->key == SQUOTE))
					ptr2->next->key = INFILE;
				else if (ptr2 && ptr2->key == LESSER)
				{
					ft_del_page(dic, ptr2);
					ptr1->key = HEREDOC;
					ptr2 = ptr1->next;
					if (ptr2)
						ptr2->key = LIMITER;
					else
						g_glob.exit_status = SYNTAX_ERROR;
				}
				else
					g_glob.exit_status = SYNTAX_ERROR;
			}
			else
				g_glob.exit_status = SYNTAX_ERROR;
		}
		else if (ptr1->key == GREATER)
		{
			if (ptr1->next)
			{
				ptr2 = ptr1->next;
				if (ptr2 && ptr2->key == CMD)
					ptr2->key = OUTFILE;
				else if (ptr2 && (ptr2->key == DQUOTE || ptr2->key == SQUOTE))
					ptr2->next->key = OUTFILE;
				else if (ptr2 && ptr2->key == GREATER)
				{
					ft_del_page(dic, ptr2);
					ptr1->key = APPEND;
					ptr2 = ptr1->next;
					if (ptr2)
						ptr2->key = OUTFILE;
					else
						g_glob.exit_status = SYNTAX_ERROR;
				}
				else
					g_glob.exit_status = SYNTAX_ERROR;
			}
			else
				g_glob.exit_status = SYNTAX_ERROR;
		}
		else if (ptr1->key == PIPE)
		{
			if (ptr1->next)
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

void	ft_new_line(int signum)
{
	(void) signum;
	rl_on_new_line();
	rl_redisplay();
}

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
			else if (input[i] && ft_is_delimiter(input[i]) == LESSER)
				ft_addpage_back(&dic, ft_pagenew(LESSER, "<\0"));
			else if (input[i] && ft_is_delimiter(input[i]) == GREATER)
				ft_addpage_back(&dic, ft_pagenew(GREATER, ">\0"));
			else if (input[i] && ft_is_delimiter(input[i]) == PIPE)
				ft_addpage_back(&dic, ft_pagenew(PIPE, "|\0"));
		}
		i += j + 1;
	}
	return(dic);
}

int	ft_is_delimiter(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (SPACE);
	else if (c == '\'')
		return (SQUOTE);
	else if (c == '\"')
		return (DQUOTE);
	else if (c == '<')
		return (LESSER);
	else if (c == '>')
		return (GREATER);
	else if (c == '|')
		return (PIPE);
	return (0);
}

t_dic	*ft_pagenew(int key, char *value)
{
	t_dic	*head;

	head = ft_malloc(sizeof(t_dic));
	if (!head)
		exit (UNSPECIFIED_ERROR);
	head->key = key;
	head->pipe = 0;
	head->value = value;
	head->next = NULL;
	head->previous = NULL;
	return (head);
}

void	ft_del_page(t_dic **dic, t_dic *page)
{
	t_dic	*ptr;
	t_dic	*prev;
	t_dic	*next;

	ptr = *dic;
	while(ptr)
	{
		if (ptr == page)
		{
			prev = ptr->previous;
			next = ptr->next;
			if (prev)
				prev->next = next;
			if (next)
				next->previous = prev;
			break;
		}
		ptr = ptr->next;
	}
}

t_dic	*ft_lastpage(t_dic *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

void	ft_addpage_back(t_dic **lst, t_dic *new)
{
	t_dic	*ptr1;
	t_dic	*ptr2;

	if (*lst)
	{
		ptr1 = ft_lastpage(*lst);
		ptr1->next = new;
		ptr1 = *lst;
		ptr2 = *lst;
		while (ptr1)
		{
			ptr1 = ptr1->next;
			if (ptr1)
				ptr1->previous = ptr2;
			ptr2 = ptr1;
		}
	}
	else
		*lst = new;
}

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	g_glob.env = env;
	g_glob.paths = ft_get_paths(g_glob.env);
	signal(SIGINT, &ft_new_line);
	ft_prompt();

	return (0);
}