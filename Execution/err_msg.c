/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 02:46:00 by ibel-har          #+#    #+#             */
/*   Updated: 2023/08/07 02:34:26 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pfd_err_msg(char *pfd)
{
	ft_putstr_fd(pfd, 2);
	ft_putstr_fd(": failed\n", 2);
	exit (1);
}

void	permission_err_msg(char *cmd)
{
	ft_dprintf(2, "%s : permission denied\n", cmd);
	exit(126);
}

void	cmd_err_msg(char *cmd)
{
	if (!cmd)
		exit (0);
	ft_dprintf(2, "%s : command not found\n", cmd);
	exit(127);
}

void	isdir_err_msg(char *cmd)
{
	ft_dprintf(2, "%s : is a directory\n", cmd);
	exit(126);
}

void	isndir_err_msg(char *cmd)
{
	ft_dprintf(2, "%s : no such file or directory\n", cmd);
	exit(127);
}
