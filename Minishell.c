/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:23:14 by nabboune          #+#    #+#             */
/*   Updated: 2023/07/21 15:53:35 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	// (void) env;
	g_glob.env = env_init(env);
	// g_glob.paths = ft_get_paths(g_glob.env);
	signal(SIGINT, &ft_new_line);
	ft_prompt();

	return (0);
}