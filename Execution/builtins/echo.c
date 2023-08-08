/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:45:25 by ibel-har          #+#    #+#             */
/*   Updated: 2023/08/08 05:45:11 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	echo_norm(char *cmd, int *i, int *j, int *nl)
{
	if (ft_strncmp(cmd, "-n", 1) == 0)
	{
		*j = 2;
		while (cmd[*j] && cmd[*j] == 'n')
			*j = *j + 1;
		if (!cmd[*j])
		{
			*nl = 1;
			*i = *i + 1;
			return (1);
		}
	}
	return (0);
}

int	ft_echo(t_parsing_output *cmd)
{
	int	i;
	int	j;
	int	nl;
	int	status;

	i = 1;
	nl = 0;
	status = 0;
	while (cmd->cmd[i])
	{
		if (echo_norm(cmd->cmd[i], &i, &j, &nl) == 1)
			continue ;
		ft_putstr_fd(cmd->cmd[i], cmd->fd_outfile);
		if (cmd->cmd[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (nl == 0)
		ft_putchar_fd('\n', cmd->fd_outfile);
	return (status);
}
