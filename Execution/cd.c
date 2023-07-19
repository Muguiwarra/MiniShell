/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 07:55:14 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/19 10:24:52 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	cd_path(t_env **env, char *path)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd");
		exit(1);
	}
	if (chdir(path) == -1)
	{
		perror("chdir");
		exit(1);
	}
	else
	{
		var_export(env, "OLDPWD", cwd, 0);
		var_export(env, "PWD", path, 0);
	}
	free(cwd);
}

void	cd_home(t_env **env, char *path)
{
	char	*home;

	(void) path;
	home = get_t_env(*env, "HOME");
	if (home == NULL)
	{
		printf("minishell: cd: HOME not set\n");
		return ;
	}
	else
	{
		cd_path(env, home);
	}
}

// cd - : go to the previous directory you were in

void	cd_prevwd(t_env **env, char *path)
{
	char	*oldpwd;

	(void) path;
	oldpwd = get_t_env(*env, "OLDPWD");
	if (oldpwd == NULL)
	{
		printf("minishell: cd: OLDPWD not set\n");
		return ;
	}
	else
	{
		cd_path(env, oldpwd);
	}
}
