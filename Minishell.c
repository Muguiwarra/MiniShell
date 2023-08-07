/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:23:14 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/06 21:14:42 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	g_glob.env = env_init(env);
	// signal(SIGINT, ft_new_line);
	// signal(SIGQUIT, SIG_IGN);
	// signal(SIGSEGV, ft_new_line);
	ft_prompt();
	return (0);
}