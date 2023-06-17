/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:23:30 by nabboune          #+#    #+#             */
/*   Updated: 2023/06/17 02:26:04 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**ft_cmd_with_null(char *cmd)
{
	char	**arr;

	arr = (char **) malloc(2 * sizeof(char *));
	arr[0] = ft_strdup(cmd);
	arr[1] = NULL;
	return (arr);
}

void	ft_prompt(char **paths, char **env)
{
	char		*input;
	t_htable	*ht;
	int			i;

	(void) env;
	(void) paths;
	while (1)
	{
		i = 0;
		signal(SIGINT, &ft_new_line);
		rl_on_new_line();
		input = readline("MiniShell-0.1$ ");
		add_history(input);
		ht = ft_hash_table(input);
		// printf("{$$}\n");
		while (ht)
		{
			ft_printf("Key : %s\nValue : %s\n\n", ht->key, ht->value);
			ht = ht->next;
		}
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

int	ft_add_arg(t_htable **ht, char *input, int i)
{
	int			j;
	t_htable	node;
	t_htable	*last_node;

	j = 0;
	while (input[i] && input[i] == ' ')
		i++;
	while (input[i + j] && input[i + j] != ' ')
		j++;
	node.key = ft_strdup("arg");
	node.value = ft_substr(input, i, j);
	last_node = (t_htable *) malloc(sizeof(t_htable));
	last_node = *ht;
	while(last_node->next)
		last_node = last_node->next;
	last_node->next = &node;

	return(j);
}

int	ft_add_cmd(t_htable **ht, char *input, int i)
{
	int			j;
	t_htable	node;
	t_htable	*last_node;

	j = 0;
	while (input[i + j] && input[i + j] != ' ')
		j++;
	node.key = ft_strdup("cmd");
	node.value = ft_substr(input, i, j);
	node.next = NULL;
	i += j;

	*ht = &node;
	last_node = (t_htable *) malloc(sizeof(t_htable));
	last_node = *ht;
	while(last_node->next)
		last_node = last_node->next;
	last_node->next = &node;

	while (input[i] == ' ')
		i++;
	if (ft_isalpha(input[i]) || input[i] == '-')
		j = ft_add_arg(ht, input, i);
	return(i + j);
}

int	ft_add_infile(t_htable **ht, char *input, int i)
{
	int			j;
	t_htable	node;
	t_htable	*last_node;

	while (input[i] == ' ')
		i++;
	j = 0;
	while (input[i + j] && input[i + j] != ' ')
		j++;
	node.key = ft_strdup("infile");
	node.value = ft_substr(input, i, j);

	last_node = (t_htable *) malloc(sizeof(t_htable));
	last_node = *ht;
	while(last_node->next)
		last_node = last_node->next;
	last_node->next = &node;

	return(i + j);
}

t_htable	*ft_hash_table(char *input)
{
	t_htable	*ht;
	int			i;

	i = 0;
	ht = (t_htable *) malloc(sizeof(t_htable));
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (ft_isalpha(input[i]))
			i = ft_add_cmd(&ht, input, i);
		else if (input[i] == '<' && input[i + 1] != '<')
			i = ft_add_infile(&ht, input, i);
	}
	return(ht);
}

int	main(int ac, char **av, char **env)
{
	char	**paths;

	(void) ac;
	(void) av;
	paths = ft_get_paths(env);
	ft_prompt(paths, env);

	return (0);
}