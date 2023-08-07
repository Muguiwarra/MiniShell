/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:07:25 by ibel-har          #+#    #+#             */
/*   Updated: 2023/08/07 03:57:10 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	her_doc_c(char *dlm, int heredoc)
{
	char	*line;
	char	*var;
	int		i;
	int		j;
	int		le;

	while (1)
	{
		line = readline("herdoc> ");
		if (!line)
		{
			free(line);
			close(heredoc);
			exit(0);
		}
		if (!ft_strcmp(line, dlm))
		{
			free(line);
			close(heredoc);
			exit(0);
		}
		i = 0;
		while (line[i])
		{
			if (line[i] == '$')
			{
				j = 1;
				if (ft_isdigit(line[i + j]))
				{
					line = ft_replace_str(line, ft_expand(ft_substr(line, i + 1, j, 1)), i, i + j);
					i++;
					continue;
				}
				if (line[i + j] && ft_is_delimiter(line[i + j]) != SPACES
					&& ft_isalnum(line[i + j]))
				{
					while (line[i + j] && ft_is_delimiter(line[i + j]) != SPACES
						&& ft_isalnum(line[i + j]))
						j++;
					var = ft_substr(line, i + 1, j - 1, 1);
					le = ft_strlen(ft_expand(var));
					line = ft_replace_str(line, ft_expand(var), i, i + j - 1);
					i += le;
					continue;
				}
			}
			i++;
		}
		ft_putendl_fd(line, heredoc);
		free(line);
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