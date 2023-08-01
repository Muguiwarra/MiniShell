/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:23:30 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/01 19:38:52 by nabboune         ###   ########.fr       */
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
		g_glob.exit_status = 0;
		rl_on_new_line();
		input = readline("MiniShell-0.1$ ");
		dic = ft_crea_dic(input);
		if (!dic)
		{
			ft_check_exit();
			ft_ending_prompt(input);
			continue ;
		}
		if (ft_check_exit())
		{
			ft_ending_prompt(input);
			continue ;
		}
		ft_check_dic(dic);
		if (ft_check_exit())
		{
			ft_ending_prompt(input);
			continue ;
		}
		ft_update_00(&dic);
		ft_check_dic(dic);
		if (ft_check_exit())
		{
			ft_ending_prompt(input);
			continue ;
		}
		ft_update_01(&dic);
		if (ft_check_exit())
		{
			ft_ending_prompt(input);
			continue ;
		}
		ft_update_02(&dic);
		if (ft_check_exit())
		{
			ft_ending_prompt(input);
			continue ;
		}
		ft_update_03(&dic);
		out = ft_parse_out(dic);
		// int	o = 0;
		// while (out)
		// {
		// 	printf("inflile : {%d}\noutfile : {%d}\n cmd : \n{", out->fd_infile, out->fd_outfile);
		// 	while (out->cmd[o])
		// 		printf("%s, ", out->cmd[o++]);
		// 	printf("}\n");
		// 	out = out->next;
		// }
		// continue;
		execute(out, env_arr(g_glob.env));
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
	if (g_glob.exit_status == UNSPECIFIED_ERROR)
	{
		ft_dprintf(2,"Minishell-0.1: Unspecified error !\n");
		return (1);
	}
	else if (g_glob.exit_status == CMD_NOT_EXECUTABLE)
	{
		ft_dprintf(2, "minishell-0.1: Command not executable !\n");
		return (1);
	}
	else if (g_glob.exit_status == CMD_NOT_FOUND)
	{
		ft_dprintf(2, "minishell-0.1: Command not found !\n");
		return (1);
	}
	else if (g_glob.exit_status == SYNTAX_ERROR)
	{
		ft_dprintf(2, "minishell-0.1: Syntax ERROR !\n");
		return (1);
	}
	else if (g_glob.exit_status == MAXIMUM_HEREDOC)
	{
		ft_dprintf(2, "minishell-0.1: Maximum HEREDOC OPENED !\n");
		return (1);
	}
	return (0);
}

void	ft_new_line(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_redisplay();
}

int	ft_is_delimiter(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
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

char	*ft_replace_str(char *original, char *new, int start, int end)
{
	char	*result;
	int		i;
	int		j;
	int		k;
	int		lo;
	int		ln;

	i = 0;
	j = 0;
	ln = ft_strlen(new);
	lo = ft_strlen(original);
	result = ft_malloc(lo - end + start + ln + 2, 1);
	while (original[i])
	{
		if (i != start)
			result[j++] = original[i++];
		else
		{
			if (ln != 0)
			{
				k = 0;
				while (new[k])
					result[j++] = new[k++];
			}
			i = end + 1;
		}
	}
	result[j] = '\0';
	return (result);
}
