/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 02:08:53 by ibel-har          #+#    #+#             */
/*   Updated: 2023/08/06 02:45:31 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_dir(char *path)
{
	struct stat path_stat;
	stat(path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
		return (1);
	else if (S_ISREG(path_stat.st_mode))
		return (2);
	return (0);
}

void cmd_err_check(char **cmd)
{
	if (!cmd)
		cmd_err_msg(" ");
	else if (*cmd == '\0' || !ft_strcmp(*cmd, " "))
		cmd_err_msg(*cmd);
	else if (ft_strchr(cmd[0], '/'))
	{
		if (check_dir(cmd[0]) && check_dir(cmd[0]) != 2)
			isdir_err_msg(cmd[0]);
		else if (check_dir(cmd[0]) == 0)
			isndir_err_msg(cmd[0]);
	}
}

void	exec_cmd(char **cmd, char **envp)
{
	char	**cmd_arr;

	cmd_err_check(cmd);
	cmd_arr = cmd_split(cmd, envp);
	if (!ft_strchr(cmd_arr[0], '/'))
		cmd_err_msg(cmd_arr[0]);
	else if ((access(cmd_arr[0], X_OK) == -1))
		permission_err_msg(cmd_arr[0]);
	else
	{
		if (execve(cmd_arr[0], cmd_arr, envp) == -1)
			cmd_err_msg(cmd_arr[0]);
	}
}

// void	exec_cmd(char **cmd, char **envp)
// {
// 	char	**cmd_arr;

// 	if (!cmd)
// 		cmd_err_msg(" ");
// 	if (*cmd == '\0' || !ft_strcmp(*cmd, " "))
// 		cmd_err_msg(*cmd);
// 	cmd_arr = cmd_split(cmd, envp);
// 	if (!ft_strchr(cmd_arr[0], '/') || (ft_strchr(cmd_arr[0], '/')
// 			&& access(cmd_arr[0], X_OK) == -1))
// 		cmd_err_msg(cmd_arr[0]);
// 	else
// 	{
// 		if (execve(cmd_arr[0], cmd_arr, envp) == -1)
// 			cmd_err_msg(cmd_arr[0]);
// 	}
// }
