/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:10:59 by nabboune          #+#    #+#             */
/*   Updated: 2023/06/17 19:01:05 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	**ft_get_paths(char **env)
{
	char	**paths;
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strnstr(env[i], "PATH", 4))
		{
			i++;
			continue ;
		}
		break ;
	}
	if (!env[i])	/* Need to review this case !!!! */
	{
		perror("Error");
		exit (1);
	}				/* Need to review this case !!!! */
	paths = ft_split(env[i] + 5, ':');
	return (paths);
}

// void	ft_exec(t_htable *ht, char **paths, char **env)
// {
// 	int		i;
// 	char	*full_path;

// 	i = 0;
// 	while (paths[i])
// 	{
// 		full_path = ft_strjoin(paths[i], "/");
// 		full_path = ft_strjoin(full_path, ht->value);
// 		if (!access(full_path, X_OK))
// 			execve (full_path, ft_cmd_with_null(ht->value), env);
// 		free(full_path);
// 		i++;
// 	}
// }
