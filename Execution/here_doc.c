/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:07:25 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/27 22:00:39 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	her_doc_c(char *dlm, int heredoc)
{
	char	*line;

	while (1)
	{
		line = readline("herdoc> ");
		if (!ft_strcmp(line, dlm))
		{
			free(line);
			close(heredoc);
			exit(0);
		}
		ft_putendl_fd(line, heredoc);
	}
}

void	here_doc(char *dlm, t_vars *vars)
{
	int	status;
	int	heredoc;

	vars->pid = fork();
	if (vars->pid == -1)
		pfd_err_msg("Fork");
	if (vars->pid == 0)
	{
		heredoc = open("./heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0666);
		her_doc_c(dlm, heredoc);
	}
	else
	{
		wait(&status);
		heredoc = open("./heredoc", O_RDONLY);
		if (dup2(heredoc, 0) == -1)
			pfd_err_msg("Dup2");
		close(heredoc);
	}
}
