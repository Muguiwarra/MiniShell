/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:23:14 by nabboune          #+#    #+#             */
/*   Updated: 2023/06/24 03:58:36 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing/parser.h"

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	g_glob.env = env;
	g_glob.paths = ft_get_paths(g_glob.env);
	signal(SIGINT, &ft_new_line);
	ft_prompt();

	return (0);
}