/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:57:38 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/19 06:54:01 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "ft_dprintf/ft_dprintf.h"


int main(int ac, char **av, char **envp)
{
	// t_env	*env;

	(void)ac;
	(void)av;
	(void)envp;

	char *msg = "file access denied \n";
	ft_dprintf(2, "minhsell : %s \n", msg);
	// "minhsell : file access denied \n" 2
	// minishell >

}