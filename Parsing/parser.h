/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:24:08 by nabboune          #+#    #+#             */
/*   Updated: 2023/06/16 23:24:00 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "../Libft/libft.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_htable
{
	char *key;
	char *value;
	struct s_htable *next;
} t_htable;

void ft_new_line(int signum);
void ft_prompt(char **paths, char **env);
char **ft_cmd_with_null(char *cmd);
void ft_new_line(int signum);
t_htable *ft_hash_table(char *input);


// To Remove : Testing
void	ft_exec(t_htable *ht, char **paths, char **env);
char	**ft_get_paths(char **env);

#endif