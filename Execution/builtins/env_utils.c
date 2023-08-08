/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:30:42 by ibel-har          #+#    #+#             */
/*   Updated: 2023/08/08 05:37:02 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*env_new(char *key, char *value, int to_free)
{
	t_env	*new;

	new = (t_env *)ft_malloc(sizeof(t_env), to_free);
	if (!new)
		return (NULL);
	if (!key)
		new->key = NULL;
	else
		new->key = ft_strdup(key, to_free);
	if (!value)
		new->value = NULL;
	else
		new->value = ft_strdup(value, to_free);
	new->next = NULL;
	return (new);
}

void	env_add_front(t_env **env, t_env *new)
{
	if (new && env)
	{
		if (*env == NULL)
		{
			*env = new;
			return ;
		}
		new->next = *env;
		*env = new;
	}
}

void	env_add_back(t_env **env, t_env *new)
{
	t_env	*last;

	if (new && env)
	{
		if (!*env)
			*env = new;
		else
		{
			last = env_last(*env);
			last->next = new;
		}
	}
}

t_env	*env_last(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}
