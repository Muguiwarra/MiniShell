/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 10:36:04 by ibel-har          #+#    #+#             */
/*   Updated: 2023/08/08 05:42:00 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	var_parse(char *str)
{
	int	i;

	i = 0;
	if (str && (ft_isalpha(str[i]) == 0 && str[i] != '_'))
		return (0);
	while (str && str[i])
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

void	var_export(t_env **env, char *key, char *value, int apnd)
{
	t_env	*tmp;
	char	*tmp_val;

	tmp = env_search(*env, key);
	tmp_val = NULL;
	if (tmp)
	{
		if (tmp->value && value)
		{
			if (apnd == 0)
				tmp_val = ft_strdup(value, 0);
			else if (apnd == 1)
				tmp_val = ft_strjoin(tmp->value, value, 0);
			free(tmp->value);
			tmp->value = tmp_val;
		}
		else if (value)
			tmp->value = ft_strdup(value, 0);
		return ;
	}
	env_add_back(env, env_new(key, value, 0));
}

int	export_cases(char **var, t_env **env)
{
	char	*tmp;
	int		pars;
	int		status;

	status = 0;
	pars = var_parse(var[0]);
	if (pars == 0 || (pars == 2 && !var[1]))
	{
		ft_dprintf(2, "export: `%s': not a valid identifier\n", var[0]);
		status = 1;
	}
	else if (pars == 2 && var[1] != NULL)
	{
		tmp = ft_substr(var[0], 0, ft_strlen(var[0]) - 1, 0);
		var_export(env, tmp, var[1], 1);
		free(tmp);
	}
	else if (pars == 1)
		var_export(env, var[0], var[1], 0);
	return (status);
}

int	ft_export(t_env **env, char **args)
{
	char	**var;
	int		status;
	int		i;

	status = 0;
	i = 1;
	if (!args[1])
		return (ft_export_print(*env));
	if (!args[1][0])
		return (ft_export_null());
	while (args[i])
	{
		var = split_var(args[i]);
		status = export_cases(var, env);
		i++;
	}
	return (status);
}

int	ft_export_null(void)
{
	ft_dprintf(2, "minishell-0.1: export: `': not a valid identifier!\n");
	return (1);
}
