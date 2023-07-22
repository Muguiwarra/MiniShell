/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:44:15 by nabboune          #+#    #+#             */
/*   Updated: 2023/07/22 19:51:07 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_expand(char *var)
{
	t_env	*env;

	env = g_glob.env;
	while (env)
	{
		if (strcmp(env->key, var) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
