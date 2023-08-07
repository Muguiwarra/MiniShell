/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:24:57 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/31 04:02:15 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_array(char **var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		free(var[i]);
		i++;
	}
	free(var);
	var = NULL;
}

char	**split_var(char *str)
{
	int	i;
	char **var;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	var = (char **)ft_malloc(sizeof(char *) * 3, 0);
	var[0] = ft_substr(str, 0, i, 0);
	if (i == (int)ft_strlen(str))
	{
		if (str[i - 1] == '=')
			var[1] = ft_strdup("");
		else
			var[1] = NULL;
	}
	else
		var[1] = ft_substr(str, i + 1, ft_strlen(str), 0);
	var[2] = NULL;
	return (var);
}

t_env	*env_init(char **envp)
{
	t_env	*env;
	char	*cwd;
	char	**var;
	int		i;

	i = 0;
	env = NULL;
	cwd = getcwd(NULL, 0);
	if (!*envp)
	{
		env_add_back(&env, env_new("PWD", cwd));
		env_add_back(&env, env_new("SHLVL", "1"));
		free(cwd);
		return (env);
	}
	while (envp[i])
	{
		var = split_var(envp[i]);
		env_add_back(&env, env_new(var[0], var[1]));
		free_array(var);
		i++;
	}
	return (env);
}

int	ft_env(t_env *env)
{
	int	status;

	status = 0;
	while (env)
	{
		if (env->value)
		{
			if (env->value[0] == '\0')
				printf("%s=\n", env->key);
			else
				printf("%s=%s\n", env->key, env->value);
		}
		env = env->next;
	}
	return (status);
}

t_env	*env_default(void)
{
	t_env	*env;
	char	*cwd;

	env = NULL;
	cwd = getcwd(NULL, 0);
	env_add_back(&env, env_new("PWD", cwd));
	env_add_back(&env, env_new("SHLVL", "1"));
	free(cwd);
	return (env);
}
/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	don't forget the default uninitialized env
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/