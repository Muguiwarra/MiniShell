/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:23:30 by nabboune          #+#    #+#             */
/*   Updated: 2023/06/18 03:00:33 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_prompt()
{
	char	*input;
	t_dic	*dic;

	while (1)
	{
		// i = 0;
		rl_on_new_line();
		input = readline("MiniShell-0.1$ ");

		// To REMOVE after
		if (ft_strncmp(input, "exit", 5) == 0)
			exit(0);
		// Remember to REMOVE IT !!!
		dic = ft_crea_dic(input);
		while (dic)
		{
			printf("Key : %d\nValue : %s\n\n", dic->key, dic->value);
			dic = dic->next;
		}
		add_history(input);
		// ft_exec(ht, paths, env);					/* To remove : Testing if the cmd is accessible */
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
	char	*word;
	t_dic	*page;
	t_dic	*last_page;
	t_dic	*dic;

	i = 0;
	open = 0;
	page = (t_dic *) malloc(sizeof(t_dic));
	while (input[i])
	{
		j = 0;
		// last_page = ft_lastpage(*dic);
		if (!ft_is_delimiter(input[i + j]))
		{
			if (open == 0)
			{
				while (!ft_is_delimiter(input[i + j]))
					j++;
				word = ft_substr(input, i, j);
				page->key = CMD;
				page->value = word;
				page->next = NULL;
				ft_addpage_back(&dic, page);
				free(word);
				free(page);
			}
			else
			{
				last_page = ft_lastpage(dic);
				while (input[i + j] != last_page->value[0])
					j++;
				word = ft_substr(input, i, j);
				page->key = CMD;
				page->value = word;
				page->next = NULL;
				ft_addpage_back(&dic, page);
				free(word);
				free(page);
			}
		}
		else
		{
			if (ft_is_delimiter(input[i]) == SQUOTE)
			{
				if (open == 0)
					open = 1;
				else
					open = 0;
				page->key = SQUOTE;
				page->value = (char *) malloc(2 * sizeof(char));
				page->value = "\'";
				page->next = NULL;
				ft_addpage_back(&dic, page);
				free(page->value);
				free(page);
			}
			else if (ft_is_delimiter(input[i]) == DQUOTE)
			{
				if (open == 0)
					open = 1;
				else
					open = 0;
				page->key = DQUOTE;
				page->value = (char *) malloc(2 * sizeof(char));
				page->value = "\"";
				page->next = NULL;
				ft_addpage_back(&dic, page);
				free(page->value);
				free(page);
			}
			else if (ft_is_delimiter(input[i]) == LESSER)
			{
				page->key = LESSER;
				page->value = (char *) malloc(2 * sizeof(char));
				page->value = "<";
				page->next = NULL;
				ft_addpage_back(&dic, page);
				free(page->value);
				free(page);
			}
			else if (ft_is_delimiter(input[i]) == GREATER)
			{
				page->key = GREATER;
				page->value = (char *) malloc(2 * sizeof(char));
				page->value = ">";
				page->next = NULL;
				ft_addpage_back(&dic, page);
				free(page->value);
				free(page);
			}
			else if (ft_is_delimiter(input[i]) == PIPE)
			{
				page->key = PIPE;
				page->value = (char *) malloc(2 * sizeof(char));
				page->value = "|";
				page->next = NULL;
				ft_addpage_back(&dic, page);
				free(page->value);
				free(page);
			}
			else if (ft_is_delimiter(input[i]) == FLAG)
			{
				page->key = GREATER;
				page->value = (char *) malloc(2 * sizeof(char));
				page->value = "-";
				page->next = NULL;
				ft_addpage_back(&dic, page);
				free(page->value);
				free(page);
			}
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
	glob.env = env;
	glob.paths = ft_get_paths(glob.env);
	signal(SIGINT, &ft_new_line);
	ft_prompt();

	return (0);
}