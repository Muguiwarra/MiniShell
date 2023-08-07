/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:44:15 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/05 23:40:17 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_expand(char *var)
{
	t_env	*env;

	env = g_glob.env;
	while (env)
	{
		if (ft_strcmp(var, "?\0") == 0)
			return (ft_itoa(g_glob.exit_stat));
		if (ft_strcmp(env->key, var) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
