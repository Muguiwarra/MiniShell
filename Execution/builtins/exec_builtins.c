/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 04:11:52 by ibel-har          #+#    #+#             */
/*   Updated: 2023/08/07 04:02:40 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

int	builtins(t_parsing_output *cmd, t_env **env)
{
	int	status;

	status = 0;
	if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		status = ft_cd(env, cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		status = ft_echo(cmd);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		status = ft_env(*env);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
	{
		status = ft_exit(cmd->cmd);
		if (g_glob.cmds_count == 1 && status != -1)
			exit(status);
		else if (status == -1)
			status = 1;
	}
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		status = ft_export(env, cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		status = ft_pwd();
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		status = ft_unset(env, cmd->cmd);
	g_glob.exit_status = status;
	return (status);
}
