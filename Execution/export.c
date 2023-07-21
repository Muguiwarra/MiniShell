/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:36:04 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/21 17:39:42 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_var_parse(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) == 0)
		return (0);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
		{
			if (str[i] == '+' && str[i + 1] == '\0')
				return (2);
			return (0);
		}
		i++;
	}
	return (1);
}

void	var_export(t_env **env, char *key, char *value, int j)
{
	t_env	*tmp;
	char	*tmp_val;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (tmp->value && j == 0)
			{
				free(tmp->value);
				tmp->value = ft_strdup(value);
			}
			else if (tmp->value && j == 1)
			{
				tmp_val = ft_strjoin(tmp->value, value, 0);
				free(tmp->value);
				tmp->value = tmp_val;
			}
			return ;
		}
		tmp = tmp->next;
	}
	env_add_back(env, env_new(key, value));
}

// exprcting an array of **arguments like: "key=value"

void	ft_export(t_env **env, char **args)
{
	int		i;
	int		pars;
	char	**var;
	char	*tmp;

	i = 0;
	while (args[i])
	{
		var = split_var(args[i]);
		pars = env_var_parse(var[0]);
		if (pars == 0 || (pars == 2 && var[1] == NULL))
			printf("export: `%s': not a valid identifier\n", var[0]);
		// don't forget to exit and update the exit status
		else if (pars == 2 && var[1] != NULL)
		{
			tmp = ft_substr(var[0], 0, ft_strlen(var[0]) - 1, 0);
			var_export(env, tmp, var[1], 1);
			free(tmp);
		}
		else
			var_export(env, var[0], var[1], 0);
		free_array(var);
		i++;
	}
}
