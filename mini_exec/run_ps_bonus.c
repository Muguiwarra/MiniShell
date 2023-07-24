/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ps_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:29:03 by ibel-har          #+#    #+#             */
/*   Updated: 2023/03/25 08:38:16 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	fd_redirect_c(int *fd, t_vars *vars)
{
	if (vars->count == vars->argc - 2)
	{
		check_outfile(vars->argv, vars);
		if (dup2(vars->outfile, 1) == -1)
			pfd_err_msg("Dup2");
		close(vars->outfile);
	}
	else
	{
		if (dup2(fd[1], 1) == -1)
			pfd_err_msg("Dup2");
	}
	close(fd[0]);
	close(fd[1]);
}

void	fd_redirect_p(int *fd, t_vars *vars)
{
	if (vars->count != vars->argc - 2)
	{
		if (dup2(fd[0], 0) == -1)
			pfd_err_msg("Dup2");
	}
	else
	{
		if (dup2(vars->std_in, 0) == -1)
			pfd_err_msg("Dup2");
		close(vars->std_in);
	}
	close(fd[0]);
	close(fd[1]);
}

void	run_ps(char *cmd, t_vars *vars, char **envp)
{
	if (pipe(vars->fd) == -1)
		pfd_err_msg("Pipe");
	vars->pid = fork();
	if (vars->pid == -1)
		pfd_err_msg("Fork");
	if (vars->pid == 0)
	{
		fd_redirect_c(vars->fd, vars);
		if (vars->infile == -1 && vars->count == 2)
			exit(0);
		exec_cmd(cmd, envp);
	}
	else
		fd_redirect_p(vars->fd, vars);
}
