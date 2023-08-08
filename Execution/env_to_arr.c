/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:18:17 by ibel-har          #+#    #+#             */
/*   Updated: 2023/08/08 04:51:48 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	env_size(t_env *env)
{
	int		len;
	t_env	*tmp;

	len = 0;
	tmp = env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

char	**env_arr(t_env *env)
{
	char	**arr;
	char	*tmp;
	int		i;

	arr = (char **)ft_malloc(sizeof(char *) * (env_size(env) + 1), 1);
	i = 0;
	while (env)
	{
		arr[i] = ft_strjoin(env->key, "=", 1);
		tmp = arr[i];
		arr[i] = ft_strjoin(arr[i], env->value, 1);
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
