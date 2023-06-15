/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:24:08 by nabboune          #+#    #+#             */
/*   Updated: 2023/06/15 23:46:47 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../Libft/libft.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	s_hash_entrie {
	char	*key;
	char	*value;
	struct s_hash_entrie	*next;
}				t_hash_entrie;

typedef struct	s_ht {
	t_hash_entrie	**ht;
}				t_ht;

#endif