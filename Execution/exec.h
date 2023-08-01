/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:38:08 by ibel-har          #+#    #+#             */
/*   Updated: 2023/08/01 16:31:46 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <stdarg.h>
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
// void			free_array(char **var);

// ************************************************************************** //
// execution
// ************************************************************************** //

char	**cmd_split(char **cmd, char **envp);
char	*add_char(char *str, char dlm, char to_add);
// void	check_args(int argc, char **argv, t_vars *vars);
// void	check_infile(char **argv, t_vars *vars);
// void	check_outfile(char **argv, t_vars *vars);
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
void	free_array(char **var);
char	**split_var(char *str);

// ERROR HANDLING

void	pfd_err_msg(char *pfd);
void	file_err_msg(char *file);
void	cmd_err_msg(char *cmd);
void	arg_err_msg(void);
void	arg_err_msg_multi(void);

#endif