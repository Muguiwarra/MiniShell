/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:24:08 by nabboune          #+#    #+#             */
/*   Updated: 2023/07/23 16:31:53 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../Libft/libft.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

// What is writted

#define CMD 0
// #define ARG 1
#define INFILE 2
#define OUTFILE 3
#define SQUOTE 4
#define DQUOTE 5
// #define SSTRING 6
// #define DSTRING 7
#define DOLLAR 8
#define LESSER 9
#define GREATER 10
#define HEREDOC 11
#define LIMITER 12
#define APPEND 13
#define PIPE 14
#define SPACE 15
#define VAR 16

typedef struct	s_dict
{
	int				key;
	int				special;
	int				pipe;
	char			*value;
	struct s_dict	*next;
}				t_dict;

typedef struct	s_parsout
{
	char				**cmd;
	int					fd_infile;
	int					fd_outfile;
	struct	s_parsout	*next;
}				t_parsout;

#endif