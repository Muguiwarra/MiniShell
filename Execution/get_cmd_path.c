/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:28:40 by ibel-har          #+#    #+#             */
/*   Updated: 2023/08/08 00:38:24 by ibel-har         ###   ########.fr       */
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
	s_cmd = ft_strjoin("/", cmd, 1);
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], s_cmd, 1);
		if (access(cmd_path, X_OK) == -1)
			cmd_path = NULL;
		else
		{
			s_cmd = NULL;
			return (cmd_path);
		}
		i++;
	}
	s_cmd = NULL;
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

char	**cmd_split(char **cmd, char **envp)
{
	char	*tmp;
	char	*path_str;
	char	*path;

	if (!ft_get_env(envp, "PATH="))
		return (cmd);
	if (!ft_strchr(cmd[0], '/') && *cmd[0] != '\0')
	{
		path_str = add_char(ft_get_env(envp, "PATH="), ':', '.');
		path = check_path(cmd[0], path_str);
		if (ft_strcmp(path, cmd[0]) == 0)
			return (cmd);
		tmp = cmd[0];
		cmd[0] = path;
		free(tmp);
		tmp = NULL;
		free(path_str);
		path_str = NULL;
	}
	return (cmd);
}
