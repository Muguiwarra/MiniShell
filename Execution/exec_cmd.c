/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 02:08:53 by ibel-har          #+#    #+#             */
/*   Updated: 2023/03/22 02:28:56 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(char *cmd, char **envp)
{
	char	**cmd_arr;

	if (*cmd == '\0' || ft_strncmp(cmd, " ", ft_strlen(cmd)) == 0)
		cmd_err_msg(cmd);
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
