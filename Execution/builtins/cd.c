/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 07:55:14 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/31 05:36:54 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_t_env(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	cd_path(t_env **env, char *path)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		ft_dprintf(2, "minishell: cd: %s\n", strerror(errno));
		return (1);
	}
	if (chdir(path) == -1)
	{
		perror("cd");
		free(cwd);
		return (1);
	}
	else
	{
		var_export(env, "OLDPWD", cwd, 0);
		var_export(env, "PWD", path, 0);
	}
	free(cwd);
	return (0);
}

int	cd_home(t_env **env)
{
	char	*home;
	int		status;

	status = 0;
	home = get_t_env(*env, "HOME");
	if (home == NULL)
	{
		ft_dprintf(2,"minishell: cd: HOME not set\n");
		status = 1;
	}
	else
		status = cd_path(env, home);
	return (status);
}

// cd - : go to the previous directory you were in

int	cd_prevwd(t_env **env)
{
	char	*oldpwd;
	int		status;

	status = 0;
	oldpwd = get_t_env(*env, "OLDPWD");
	if (oldpwd == NULL)
	{
		ft_dprintf(2, "minishell: cd: OLDPWD not set\n");
		status = 1;
	}
	else
		status =  cd_path(env, oldpwd);
	return (status);
}

int ft_cd(t_env **env, char **args)
{
	int	status;

	status = 0;
	if (args[1] == NULL)
		status = cd_home(env);
	else if (ft_strcmp(args[1], "-") == 0)
		status = cd_prevwd(env);
	else
		status = cd_path(env, args[1]);
	return (status);
}
