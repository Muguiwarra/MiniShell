/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:23:30 by nabboune          #+#    #+#             */
/*   Updated: 2023/06/25 08:36:00 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_prompt()
{
	char	*read;
	char	*input;
	t_dic	*dic;
	// t_parsing_output	*out;

	while (1)
	{
		g_glob.exit_status = 0;
		rl_on_new_line();
		read = readline("MiniShell-0.1$ ");
		input = ft_rm_end_sp(read);

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
		ft_rm_sp(&dic, 0);
		while (dic)
		{
			printf("Present : %p\nKey : %d\nValue : %s\nNext : %p\nPrevious : %p\n\n", dic, dic->key, dic->value, dic->next, dic->previous);
			dic = dic->next;
		}
		ft_ending_prompt(read);
	}
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

void	ft_new_line(int signum)
{
	(void) signum;
	rl_on_new_line();
	rl_redisplay();
}

int	ft_is_delimiter(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
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
	else if (c == '$')
		return (DOLLAR);
	return (0);
}
