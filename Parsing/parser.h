/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:24:08 by nabboune          #+#    #+#             */
/*   Updated: 2023/07/31 06:25:17 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../Libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>

// What is writted

# define CMD 0
// #define ARG 1
# define INFILE 2
# define OUTFILE 3
# define SQUOTE 4
# define DQUOTE 5
// #define SSTRING 6
// #define DSTRING 7
# define DOLLAR 8
# define LESSER 9
# define GREATER 10
# define HEREDOC 11
# define LIMITER 12
# define APPEND 13
# define PIPE 14
# define SPACE 15
# define VAR 16

typedef struct s_dic
{
	int						key;
	int						special;
	int						pipe;
	char					*value;
	struct s_dic			*next;
	struct s_dic			*previous;
}							t_dic;

typedef struct s_parsing_output
{
	char					**cmd;
	int						fd_infile;
	int						fd_outfile;
	struct s_parsing_output	*next;
}							t_parsing_output;

int							ft_is_delimiter(char c);
void						ft_new_line(int signum);
void						ft_prompt(void);
void						ft_ending_prompt(char *input);

void						ft_addpage_back(t_dic **lst, t_dic *new);
t_dic						*ft_pagenew(int key, char *value, int pipe);
void						ft_del_page(t_dic **dic, t_dic *page);
t_dic						*ft_lastpage(t_dic *lst);

t_parsing_output			*ft_newpipe(int in, int out, char **cmd);
t_parsing_output			*ft_lastpipe(t_parsing_output *lst);
void	ft_addpipe_back(t_parsing_output **lst,
						t_parsing_output *new);

t_dic						*ft_crea_dic(char *input);
int							ft_open_quotes(t_dic **dic, char *input, int pipe,
								int i);
void						ft_check_dic(t_dic *dic);
void						ft_update_00(t_dic **dic);
void						ft_new_update_dic(t_dic **dic);
void						ft_less_great(t_dic **dic, t_dic *ptr1,
								int operation);
void						ft_rm_multi_sp(t_dic **dic);
int							ft_check_exit(void);
int							ft_get_limiter(t_dic **dic, char *input, int i,
								int pipe);
int							ft_open_infile(t_dic *dic);

char						*ft_expand(char *var);
char						*ft_replace_str(char *original, char *new,
								int start, int end);
void						ft_update_01(t_dic **dic);
void						ft_update_02(t_dic **dic);

int							ft_pipes(t_dic *dic);
int							ft_nb_infiles(t_dic *dic, int pipe);
int							ft_nb_outfiles(t_dic *dic, int pipe);
int							ft_nb_cmd(t_dic *dic, int pipe);
int							ft_infile(t_dic *dic, int in, int pipe);
int							ft_outfile(t_dic *dic, int out, int pipe);
char						**ft_getcmd(t_dic *dic, int nb_cmd, int pipe);
t_parsing_output			*ft_parse_out(t_dic *dic);

// To Remove : Testing
// void	ft_exec(char **paths, char **env);
// char	**ft_get_paths(char **env);
// void	ft_ending_prompt_exec(char *input);

#endif