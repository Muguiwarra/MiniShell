/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:38:08 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/22 23:05:16 by ibel-har         ###   ########.fr       */
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


typedef struct vars
{
	char	**argv;
	int		pid;
	int		fd[2];
	int		std_in;
	int		argc;
	int		count;
	int		infile;
	int		outfile;
}	t_vars;

// ************************************************************************** //
// builtins
// ************************************************************************** //

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

// ************************************************************************** //
// execution
// ************************************************************************** //


char	**cmd_split(char *cmd, char **envp);
char	*add_char(char *str, char dlm, char to_add);
void	check_args(int argc, char **argv, t_vars *vars);
void	check_input_file(char **argv, t_vars *vars);
void	check_output_file(char **argv, t_vars *vars);
void	run_ps(char *cmd, t_vars *vars, char **envp);
void	fd_redirect_c(int *fd, t_vars *vars);
void	fd_redirect_p(int *fd, t_vars *vars);
void	exec_cmd(char *cmd, char **envp);
void	check_infile(char **argv, t_vars *vars);
void	check_outfile(char **argv, t_vars *vars);
void	check_args_bonus(int argc, char **argv, t_vars *vars);
void	here_doc(char **argv, t_vars *vars);

// ERROR HANDLING

void	pfd_err_msg(char *pfd);
void	file_err_msg(char *file);
void	cmd_err_msg(char *cmd);
void	arg_err_msg(void);
void	arg_err_msg_multi(void);






#endif