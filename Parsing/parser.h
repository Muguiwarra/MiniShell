/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:24:08 by nabboune          #+#    #+#             */
/*   Updated: 2023/06/23 05:50:03 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "../Libft/libft.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

// What is writted

#define CMD 0
#define ARG 1
#define INFILE 2
#define OUTFILE 3
#define SQUOTE 4
#define DQUOTE 5
#define SSTRING 6
#define DSTRING 7
#define DOLLAR 8
#define LESSER 9
#define GREATER 10
#define HEREDOC 11
#define LIMITER 12
#define APPEND 13
#define PIPE 14
#define SPACE 15

// Exit Status

#define SUCCES 0
#define UNSPECIFIED_ERROR 1
#define MAXIMUM_HEREDOC 2
#define CMD_NOT_EXECUTABLE 126
#define CMD_NOT_FOUND 127
#define SYNTAX_ERROR 258

typedef struct	s_dic
{
	int				key;
	int				pipe;
	char			*value;
	struct s_dic	*next;
	struct s_dic	*previous;
}				t_dic;

typedef struct	s_parsing_output
{
	char	**cmd;
	int		fd_infile;
	int		fd_outfile;
}				t_parsing_output;

typedef struct	s_global
{
	char	**env;
	char	**paths;
	int		exit_status;
	int		exit_stat;
	t_list	*allocations;
}				t_global;

t_global			g_glob;
int					ft_is_delimiter(char c);
void				ft_new_line(int signum);
void				ft_prompt();
void				ft_ending_prompt(char *input);
void				ft_addpage_back(t_dic **lst, t_dic *new);
t_dic				*ft_pagenew(int key, char *value);
void				ft_del_page(t_dic **dic, t_dic *page);
t_dic				*ft_lastpage(t_dic *lst);
t_dic				*ft_crea_dic(char *input);
void				ft_check_dic(t_dic *dic);
void				ft_update_dic(t_dic **dic);
int					ft_check_exit();
int					ft_open_infile(t_dic *dic);
t_parsing_output	*ft_parsing_output(t_dic *dic);

// To Remove : Testing
void	ft_exec(char **paths, char **env);
char	**ft_get_paths(char **env);
void	ft_ending_prompt_exec(char *input);

#endif