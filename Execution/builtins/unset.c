/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:35:34 by ibel-har          #+#    #+#             */
/*   Updated: 2023/08/07 16:55:30 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	delete_env_var(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;

	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (prev == NULL)
				*env = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	unset_parse(char *str)
{
	int	i;

	i = 0;
	if (str && (ft_isalpha(str[i]) == 0 && str[i] != '_'))
		return (0);
	while (str && str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_unset(t_env **env, char **keys)
{
	int	i;
	int	status;

	status = 0;
	i = 1;
	while (keys[i])
	{
		if (unset_parse(keys[i]) == 0)
		{
			printf("minishell: unset: `%s': not a valid identifier\n", keys[i]);
			status = 1;
		}
		else
			delete_env_var(env, keys[i]);
		i++;
	}
	return (status);
}