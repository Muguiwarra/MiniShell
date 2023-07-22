/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:24:25 by ibel-har          #+#    #+#             */
/*   Updated: 2023/03/22 02:14:35 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_infile(char **argv, t_vars *vars)
{
	if (!ft_strncmp(argv[1], "here_doc", 8) && ft_strlen(argv[1]) == 8)
	{
		vars->count = 3;
		vars->infile = -1;
	}
	else
	{
		vars->infile = open(argv[1], O_RDONLY);
		if (vars->infile == -1)
			perror(argv[1]);
		vars->count = 2;
	}
}

void	check_outfile(char **argv, t_vars *vars)
{
	if (!ft_strncmp(argv[1], "here_doc", 8) && ft_strlen(argv[1]) == 8)
	{
		vars->outfile = open(argv[vars->argc - 1], O_WRONLY | O_CREAT
				| O_APPEND, 0644);
		if (vars->outfile == -1)
		{
			perror(argv[vars->argc - 1]);
			exit(1);
		}
	}
	else
	{
		vars->outfile = open(argv[vars->argc - 1], O_WRONLY | O_CREAT
				| O_TRUNC, 0644);
		if (vars->outfile == -1)
		{
			perror(argv[vars->argc - 1]);
			exit(1);
		}
	}
}

void	check_args_bonus(int argc, char **argv, t_vars *vars)
{
	if (argc < 5)
		arg_err_msg_multi();
	vars->argc = argc;
	vars->argv = argv;
	check_infile(argv, vars);
}
