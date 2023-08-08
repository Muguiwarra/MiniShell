/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:07:25 by ibel-har          #+#    #+#             */
/*   Updated: 2023/08/08 06:16:17 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_err_line(char *line, int heredoc)
{
	free(line);
	close(heredoc);
	exit(0);
}

int	ft_her_doc_c_core_00(char *line, int *i, int *j)
{
	*j = 1;
	if (ft_isdigit(line[*i + *j]))
	{
		line = ft_replace_str(line, ft_expand(ft_substr(line, *i + 1, *j, 1)),
				*i, *i + *j);
		(*i)++;
		return (1);
	}
	return (0);
}

void	her_doc_c(char *dlm, int heredoc)
{
	t_variables	var;

	while (1)
	{
		ft_pre_her_doc_c(&var, heredoc, dlm);
		while (var.line[var.i])
		{
			if (var.line[var.i] == '$')
			{
				if (ft_her_doc_c_core_00(var.line, &var.i, &var.j))
					continue ;
				var.tmp_char = var.line[var.i + var.j];
				while (var.tmp_char && ft_isalnum(var.tmp_char)
					&& ft_is_delimiter(var.tmp_char) != SPACES)
				{
					var.j++;
					var.tmp_char = var.line[var.i + var.j];
				}
				ft_post_her_doc_c(&var);
				continue ;
			}
			var.i++;
		}
		ft_postpost_herdoc(&var, heredoc);
	}
}

int	here_doc(char *dlm)
{
	char	*file_name;
	int		status;
	int		heredoc;
	int		pid;

	file_name = ft_strjoin("/tmp/", randfn(5), 1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		pfd_err_msg("Fork");
	if (pid == 0)
	{
		heredoc = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		signal(SIGINT, ft_exit_heredoc);
		her_doc_c(dlm, heredoc);
		close(heredoc);
	}
	else
	{
		wait(&status);
		heredoc = open(file_name, O_RDONLY);
	}
	return (heredoc);
}

void	ft_exit_heredoc(int signum)
{
	(void) signum;
	rl_on_new_line();
	rl_redisplay();
	g_glob.exit_heredoc = 1;
	exit(1);
}
