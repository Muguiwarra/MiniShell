/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:54:12 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/27 22:00:39 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*check_path(char *cmd, char *path_str)
{
	int		i;
	char	**paths;
	char	*cmd_path;
	char	*s_cmd;

	i = 0;
	paths = ft_split(path_str, ':');
	s_cmd = ft_strjoin("/", cmd);
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], s_cmd);
		if (access(cmd_path, X_OK) == -1)
			ft_free(&cmd_path);
		else
		{
			ft_free(&s_cmd);
			ft_freearr(paths);
			return (cmd_path);
		}
		i++;
	}
	ft_free(&s_cmd);
	ft_freearr(paths);
	return (cmd);
}

char	*ft_get_env(char **envp, char *var)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, ft_strlen(var)))
			return (&envp[i][ft_strlen(var)]);
		i++;
	}
	return (NULL);
}

char	**cmd_split(char *cmd, char **envp)
{
	char	**cmd_arr;
	char	*tmp;
	char	*path_str;
	char	*path;

	cmd_arr = ft_split(cmd, ' ');
	if (!ft_get_env(envp, "PATH="))
		return (cmd_arr);
	if (!ft_strchr(cmd_arr[0], '/'))
	{
		path_str = add_char(ft_get_env(envp, "PATH="), ':', '.');
		path = check_path(cmd_arr[0], path_str);
		tmp = cmd_arr[0];
		cmd_arr[0] = path;
		ft_free(&tmp);
		ft_free(&path_str);
	}
	return (cmd_arr);
}
