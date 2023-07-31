/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 02:08:53 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/30 22:58:02 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_cmd(char **cmd, char **envp)
{
	char	**cmd_arr;

	if (!cmd)
		cmd_err_msg(" ");
	if (*cmd == '\0' || !ft_strcmp(*cmd, " "))
		cmd_err_msg(*cmd);
	cmd_arr = cmd_split(cmd, envp);
	if (!ft_strchr(cmd_arr[0], '/') || (ft_strchr(cmd_arr[0], '/')
			&& access(cmd_arr[0], X_OK) == -1))
		cmd_err_msg(cmd_arr[0]);
	else
	{
		if (execve(cmd_arr[0], cmd_arr, envp) == -1)
			cmd_err_msg(cmd_arr[0]);
	}
}
