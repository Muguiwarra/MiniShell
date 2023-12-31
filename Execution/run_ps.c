/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ps.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:29:03 by ibel-har          #+#    #+#             */
/*   Updated: 2023/08/08 05:45:31 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	ft_exit_sp(int signum)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit(signum + 128);
}

void	run_ps(t_parsing_output *cmd, t_vars *vars, char **envp)
{
	if (pipe(vars->fd) == -1)
		pfd_err_msg("Pipe");
	signal(SIGINT, SIG_IGN);
	vars->pid = fork();
	if (vars->pid == -1)
		pfd_err_msg("Fork");
	if (vars->pid == 0)
	{
		signal(SIGINT, ft_exit_sp);
		output_rdir(cmd, vars);
		if (is_builtin(cmd->cmd[0]))
			exit(builtins(cmd, &g_glob.env));
		else
			exec_cmd(cmd->cmd, envp);
	}
	else
		input_rdir(cmd, vars);
}
