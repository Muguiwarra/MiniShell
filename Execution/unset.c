/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:35:34 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/10 16:09:09 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
	if (ft_isalpha(str[i]) == 0)
		return (0);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	unset(t_env **env, char **keys)
{
	int	i;

	i = 0;
	while (keys[i])
	{
		if (unset_parse(keys[i]) == 0)
		{
			printf("minishell: unset: `%s': not a valid identifier\n", keys[i]);
			// dont forget to update the exit status
		}
		else
			delete_env_var(env, keys[i]);
		// dont forget to update the exit status
	}
}