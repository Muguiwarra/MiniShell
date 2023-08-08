/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:22:46 by ibel-har          #+#    #+#             */
/*   Updated: 2023/08/08 05:16:43 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_vars(t_vars *vars, t_parsing_output *cmds)
{
	vars->count = 0;
	vars->std_in = dup(0);
	vars->std_out = dup(1);
	vars->tmp = cmds;
}

int	wait_for_childs(t_vars vars, int *status)
{
	waitpid(vars.pid, status, 0);
	while (wait(NULL) != -1)
		;
	if (WIFEXITED(*status))
		return (WEXITSTATUS(*status));
	else if (WIFSIGNALED(*status))
		return (128 + *status);
	return (*status);
}

void	close_fds(t_vars *vars)
{
	while (vars->tmp)
	{
		if (vars->tmp->fd_infile > 1)
			close(vars->tmp->fd_infile);
		if (vars->tmp->fd_outfile > 1)
			close(vars->tmp->fd_outfile);
		vars->tmp = vars->tmp->next;
	}
	close(vars->std_in);
	close(vars->std_out);
}

int	execute(t_parsing_output *cmds, char **envp)
{
	t_vars	vars;
	int		status;

	init_vars(&vars, cmds);
	if (vars.std_in == -1)
		pfd_err_msg("Dup");
	g_glob.cmds_count = out_len(cmds);
	if (g_glob.cmds_count == 1 && is_builtin(cmds->cmd[0]))
		return (builtins(cmds, &g_glob.env));
	while (cmds)
	{
		if (vars.count == 0 && cmds->fd_infile > 0)
			ft_dup2(cmds->fd_infile, 0);
		if (cmds->fd_infile != -1)
			run_ps(cmds, &vars, envp);
		cmds = cmds->next;
		vars.count++;
	}
	dup2(vars.std_in, 0);
	if (vars.std_out != -1)
		dup2(vars.std_out, 1);
	close_fds(&vars);
	status = wait_for_childs(vars, &status);
	return (status);
}
