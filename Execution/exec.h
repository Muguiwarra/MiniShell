/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:38:08 by ibel-har          #+#    #+#             */
/*   Updated: 2023/08/07 04:03:03 by nabboune         ###   ########.fr       */
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
# include <errno.h>
# include <stdarg.h>
# include <dirent.h>
# include <sys/stat.h>
# include "../Parsing/parser.h"
# include "../Libft/libft.h"

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct vars
{
	int		pid;
	int		fd[2];
	int		std_in;
	int		std_out;
	int		count;
}	t_vars;

// ************************************************************************** //
// builtins
// ************************************************************************** //

// #############	cd		#############
int 	ft_cd(t_env **env, char **args);
// #############	echo	#############
int		ft_echo(t_parsing_output *out);
// #############	env		#############
t_env	*env_init(char **envp);
int		ft_env(t_env *env);
t_env	*env_default(void);
// #############	exit	#############
int		ft_exit(char **args);
// #############	export	#############
int		ft_export(t_env **env, char **args);
int		ft_export_print(t_env *env);
int		ft_export_null();
void	var_export(t_env **env, char *key, char *value, int j);
t_env	*env_search(t_env *env, char *key);
// #############	pwd		#############
int		ft_pwd(void);
// #############	unset	#############
int		ft_unset(t_env **env, char **args);
// #############	other	#############
int		builtins(t_parsing_output *cmd, t_env **env);
int		is_builtin(char *cmd);
t_env	*env_new(char *key, char *value);
void	env_add_front(t_env **env, t_env *new);
void	env_add_back(t_env **env, t_env *new);
t_env	*env_last(t_env *env);
void	env_clear(t_env **env);




// ************************************************************************** //
// execution
// ************************************************************************** //

char	**cmd_split(char **cmd, char **envp);
char	*add_char(char *str, char dlm, char to_add);
int		here_doc(char *dlm);
void	run_ps(t_parsing_output *cmd, t_vars *vars, char **envp);
void	input_rdir(t_parsing_output *cmd, t_vars *vars);
void	output_rdir(t_parsing_output *cmd, t_vars *vars);
void	ft_dup2(int fd, int std_fd);
void	exec_cmd(char **cmd, char **envp);
int		execute(t_parsing_output *cmds, char **envp);

// ERROR HANDLING

void	pfd_err_msg(char *pfd);
void	file_err_msg(char *file);
void	cmd_err_msg(char *cmd);
void	arg_err_msg(void);
void	arg_err_msg_multi(void);

// ENVIRONMENT

char	**env_arr(t_env *env);
void	env_clear(t_env **env);
char	**split_var(char *str);

// ERROR HANDLING

void	pfd_err_msg(char *pfd);
void	permission_err_msg(char *file);
void	cmd_err_msg(char *cmd);
void	isdir_err_msg(char *cmd);
void	isndir_err_msg(char *cmd);

// utils

int		array_len(char **array);
int		out_len(t_parsing_output *env);
void	free_array(char **var);

#endif