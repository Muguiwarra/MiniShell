/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:30:42 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/19 09:19:59 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*env_new(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	if (!key)
		new->key = NULL;
	else
		new->key = ft_strdup(key);
	if (!value)
		new->value = NULL;
	else
		new->value = ft_strdup(value);
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

void	env_clear(t_env **env)
{
	t_env	*tmp;

	if (!env)
		return ;
	while (*env)
	{
		tmp = (*env)->next;
		free((*env)->key);
		free((*env)->value);
		free(*env);
		*env = tmp;
	}
}