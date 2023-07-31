/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ps.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:29:03 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/30 03:31:26 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_dup2(int fd, int std_fd)
{
	if (dup2(fd, std_fd) == -1)
		pfd_err_msg("Dup2");
	if (close(fd) == -1)
		pfd_err_msg("Close");
}

void	ft_dup(int std_fd)
{
	if (dup(std_fd) == -1)
		pfd_err_msg("Dup");
}

void	input_rdir(t_parsing_output *cmd, t_vars *vars)
{
	close(vars->fd[1]);
	if (cmd->next)
	{
		if (cmd->fd_infile > 1)
			ft_dup2(cmd->fd_infile, 0);
		else if (dup2(vars->fd[0], 0) == -1)
			pfd_err_msg("Dup2");
	}
	else
	{
		if (dup2(vars->std_in, 0) == -1)
			pfd_err_msg("Dup2");
		// close(vars->std_in);
	}
	close(vars->fd[0]);
}

void	output_rdir(t_parsing_output *cmd, t_vars *vars)
{
	close(vars->fd[0]);
	if (!cmd->next)
	{
		if (cmd->fd_outfile > 1)
			ft_dup2(cmd->fd_outfile, 1);
		else
		{
			if (dup2(vars->std_out, 1) == -1)
				pfd_err_msg("Dup2");
		}
	}
	else
	{
		if (cmd->fd_outfile > 1)
			ft_dup2(cmd->fd_outfile, 1);
		else if (dup2(vars->fd[1], 1) == -1)
			pfd_err_msg("Dup2");
	}
	close(vars->fd[1]);
}

void	run_ps(t_parsing_output *cmd, t_vars *vars, char **envp)
{
	if (pipe(vars->fd) == -1)
		pfd_err_msg("Pipe");
	vars->pid = fork();
	if (vars->pid == -1)
		pfd_err_msg("Fork");
	if (vars->pid == 0)
	{
		output_rdir(cmd, vars);
		exec_cmd(cmd->cmd, envp);
	}
	else
		input_rdir(cmd, vars);
}

/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		A child process get SEGEV if the CL has "$" alone...
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/