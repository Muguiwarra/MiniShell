/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:23:30 by nabboune          #+#    #+#             */
/*   Updated: 2023/06/21 03:14:06 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_prompt()
{
	char	*input;
	t_dic	*dic;

	while (1)
	{
		rl_on_new_line();
		input = readline("MiniShell-0.1$ ");

		// To REMOVE after
		if (ft_strncmp(input, "exit", 5) == 0)
			exit(0);
		// Remember to REMOVE IT !!!
		dic = ft_crea_dic(input);
		while (dic)
		{
			printf("Present : %p\nKey : %d\nValue : %s\nNext : %p\n\n", dic, dic->key, dic->value, dic->next);
			dic = dic->next;
		}
		add_history(input);
		// ft_exec(ht, paths, env);					/* To remove : Testing if the cmd is accessible */
		ft_collect_garbadge();
		free(input);
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
			}
			else
			{
				last_page = ft_lastpage(dic);
				while (input[i + j] && input[i + j] != last_page->value[0])
					j++;
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
			else if (input[i] && ft_is_delimiter(input[i]) == FLAG)
				ft_addpage_back(&dic, ft_pagenew(FLAG, "-\0"));
		}
		i += j + 1;
	}
	return(dic);
}

int	ft_is_delimiter(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
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
	else if (c == '-')
		return (FLAG);
	return (0);
}

t_dic	*ft_pagenew(int key, char *value)
{
	t_dic	*head;

	head = ft_malloc(sizeof(t_dic));
	if (!head)
		exit (UNSPECIFIED_ERROR);
	head->key = key;
	head->value = value;
	head->next = NULL;
	return (head);
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
	t_dic	*ptr;

	if (*lst)
	{
		ptr = ft_lastpage(*lst);
		ptr->next = new;
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