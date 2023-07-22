/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:07:25 by ibel-har          #+#    #+#             */
/*   Updated: 2023/03/26 06:51:43 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	her_doc_c(char **argv, t_vars *vars)
{
	char	*line;

	close(vars->fd[0]);
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		if ((!ft_strncmp(line, argv[2], ft_strlen(argv[2])))
			&& ((ft_strlen(line) - 1) == ft_strlen(argv[2])))
		{
			free(line);
			close(vars->fd[1]);
			exit(0);
		}
		ft_putstr_fd(line, vars->fd[1]);
	}
	close(vars->fd[1]);
}

void	here_doc(char **argv, t_vars *vars)
{
	int		status;

	if (pipe(vars->fd) == -1)
		pfd_err_msg("Pipe");
	vars->pid = fork();
	if (vars->pid == -1)
		pfd_err_msg("Fork");
	if (vars->pid == 0)
		her_doc_c(argv, vars);
	else
	{
		close(vars->fd[1]);
		if (dup2(vars->fd[0], 0) == -1)
			pfd_err_msg("Dup2");
		close(vars->fd[0]);
		waitpid(vars->pid, &status, 0);
	}
}
