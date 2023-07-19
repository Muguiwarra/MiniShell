/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:24:57 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/19 09:08:45 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	var = (char **)malloc(sizeof(char *) * 3);
	var[0] = ft_substr(str, 0, i);
	if (i == (int)ft_strlen(str))
	{
		if (str[i - 1] == '=')
			var[1] = ft_strdup("");
		else
			var[1] = NULL;
	}
	else
		var[1] = ft_substr(str, i + 1, ft_strlen(str));
	var[2] = NULL;
	return (var);
}

t_env	*env_init(char **envp)
{
	t_env	*env;
	char	**var;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		var = split_var(envp[i]);
		env_add_back(&env, env_new(var[0], var[1]));
		free_array(var);
		i++;
	}
	return (env);
}

void	env_print(t_env *env)
{
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
}
