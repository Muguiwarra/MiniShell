/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:46:00 by ibel-har          #+#    #+#             */
/*   Updated: 2023/03/25 08:07:38 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pfd_err_msg(char *pfd)
{
	ft_putstr_fd(pfd, 2);
	ft_putstr_fd(": failed\n", 2);
	exit(1);
}

void	file_err_msg(char *file)
{
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": no such file or directory\n", 2);
	exit(1);
}

void	cmd_err_msg(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

void	arg_err_msg(void)
{
	ft_putstr_fd("Error: Wrong number of arguments\n", 2);
	ft_putstr_fd("Usage: ./pipex infile cmd(1) cmd(2) outfile\n", 2);
	exit(1);
}

void	arg_err_msg_multi(void)
{
	ft_putstr_fd("Error: Wrong number of arguments\n", 2);
	ft_putstr_fd("Usage: ./pipex infile cmd(1) cmd(2) ... cmd(n) outfile\n", 2);
	exit(1);
}
