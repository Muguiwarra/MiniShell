/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 08:57:48 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/01 16:31:53 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Parsing/parser.h"
# include "Execution/exec.h"
# include "src/src.h"

# define SUCCES 0
# define UNSPECIFIED_ERROR 1
# define MAXIMUM_HEREDOC 2
# define CMD_NOT_EXECUTABLE 126
# define CMD_NOT_FOUND 127
# define SYNTAX_ERROR 258
// # define PROMPT ""

typedef struct	s_global
{
	t_env	*env;
	char	**paths;
	int		exit_status;
	int		exit_stat;
	int		open;
	int		pipe;
	t_list	*allocations;
}				t_global;

t_global			g_glob;

#endif