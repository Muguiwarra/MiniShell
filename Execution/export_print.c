/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:37:52 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/19 09:08:52 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*cp_env(t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	tmp = env;
	new = NULL;
	while (tmp)
	{
		env_add_back(&new, env_new(tmp->key, tmp->value));
		tmp = tmp->next;
	}
	return (new);
}

void	alpha_sort(t_env **env)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	*key;
	char	*value;

	tmp = *env;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp->key, tmp2->key) > 0)
			{
				key = tmp->key;
				value = tmp->value;
				tmp->key = tmp2->key;
				tmp->value = tmp2->value;
				tmp2->key = key;
				tmp2->value = value;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

void	export_print(t_env *env)
{
	t_env	*penv;
	t_env	*tmp;

	penv = cp_env(env);
	alpha_sort(&env);
	tmp = env;
	while (tmp)
	{
		if (tmp->value)
		{
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		}
		else
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
	env_clear(&tmp);
}
