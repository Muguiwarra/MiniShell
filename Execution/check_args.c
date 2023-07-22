/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:24:25 by ibel-har          #+#    #+#             */
/*   Updated: 2023/03/22 02:28:41 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_input_file(char **argv, t_vars *vars)
{
	vars->infile = open(argv[1], O_RDONLY);
	if (vars->infile == -1)
		perror(argv[1]);
	vars->count = 2;
}

void	check_output_file(char **argv, t_vars *vars)
{
	vars->outfile = open(argv[vars->argc - 1], O_WRONLY | O_CREAT
			| O_TRUNC, 0644);
	if (vars->outfile == -1)
	{
		perror(argv[vars->argc - 1]);
		exit(1);
	}
}

void	check_args(int argc, char **argv, t_vars *vars)
{
	if (argc != 5)
		arg_err_msg();
	vars->argc = argc;
	vars->argv = argv;
	check_input_file(argv, vars);
}
