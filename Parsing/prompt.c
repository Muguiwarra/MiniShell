/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:23:30 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/07 17:58:21 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_prompt(void)
{
	char				*input;
	t_dic				*dic;
	t_parsing_output	*out;

	while (1)
	{
		ft_pre_prompt();
		input = readline("MiniShell-0.1$ ");
		dic = ft_crea_dic(input);
		if (ft_dic_not_created(dic, input))
			continue ;
		if (ft_check_dic_exit(dic, input))
			continue ;
		if (ft_update(&dic, input))
			continue ;
		out = ft_parse_out(dic);
		g_glob.exit_status = execute(out, env_arr(g_glob.env));
		ft_ending_prompt(input);
	}
}

void	ft_ending_prompt(char *input)
{
	add_history(input);
	ft_collect_garbadge();
	free(input);
	g_glob.exit_stat = g_glob.exit_status;
}

int	ft_check_exit(void)
{
	if (g_glob.exit_status == UNSPECIFIED_ERROR
		|| g_glob.exit_status == CMD_NOT_EXECUTABLE
		|| g_glob.exit_status == CMD_NOT_FOUND
		|| g_glob.exit_status == SYNTAX_ERROR
		|| g_glob.exit_status == MAXIMUM_HEREDOC)
	{
		if (g_glob.exit_status == UNSPECIFIED_ERROR)
			ft_dprintf(2, "Minishell-0.1: Unspecified error !\n");
		else if (g_glob.exit_status == CMD_NOT_EXECUTABLE)
			ft_dprintf(2, "minishell-0.1: Command not executable !\n");
		else if (g_glob.exit_status == CMD_NOT_FOUND)
			ft_dprintf(2, "minishell-0.1: Command not found !\n");
		else if (g_glob.exit_status == SYNTAX_ERROR)
			ft_dprintf(2, "minishell-0.1: Syntax ERROR !\n");
		else if (g_glob.exit_status == MAXIMUM_HEREDOC)
			ft_dprintf(2, "minishell-0.1: Maximum HEREDOC OPENED !\n");
		return (1);
	}
	return (0);
}

void	ft_new_line(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGSEGV)
	{
		rl_on_new_line();
		exit(0);
	}
}

int	ft_is_delimiter(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (SPACES);
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
