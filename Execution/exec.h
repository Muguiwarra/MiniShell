/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:38:08 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/19 10:05:10 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include "../Libft/libft.h"

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

t_env			*env_new(char *key, char *value);
void			env_add_back(t_env **env, t_env *new);
void			env_add_front(t_env **env, t_env *new);
t_env			*env_last(t_env *env);
void			env_clear(t_env **env);
t_env			*env_init(char **envp);
char 			**split_var(char *str);
void			env_print(t_env *env);
t_env			*cp_env(t_env *env);
void			alpha_sort(t_env **env);
void			export_print(t_env *env);
void			var_export(t_env **env, char *key, char *value, int j);
void			ft_export(t_env **env, char **args);
int				env_var_parse(char *str);
void			free_array(char **var);







#endif