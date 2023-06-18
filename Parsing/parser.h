/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:24:08 by nabboune          #+#    #+#             */
/*   Updated: 2023/06/18 02:57:49 by nabboune         ###   ########.fr       */
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
#define FLAG 15

// Exit Status

#define SUCCES 0
#define UNSPECIFIED_ERROR 1
#define CMD_NOT_EXECUTABLE 126
#define CMD_NOT_FOUND 127

typedef struct	s_dic
{
	int				key;
	char			*value;
	struct s_dic	*next;
	struct s_dic	*previous;
}				t_dic;

typedef struct	s_parsing_output
{
	char	*cmd;
	char	*arg;
	int		fd_infile;
	int		fd_outfile;
}				t_parsing_output;

typedef struct	s_global
{
	char	**env;
	char	**paths;
	int		exit_status;
}				t_global;

t_global	glob;
int			ft_is_delimiter(char c);
void		ft_new_line(int signum);
void		ft_prompt();
void		ft_addpage_back(t_dic **lst, t_dic *new);
t_dic		*ft_lastpage(t_list *lst);
t_dic		*ft_crea_dic(char *input);

// To Remove : Testing
// void	ft_exec(t_htable *ht, char **paths, char **env);
char **ft_get_paths(char **env);

#endif