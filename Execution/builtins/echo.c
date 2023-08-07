/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:45:25 by ibel-har          #+#    #+#             */
/*   Updated: 2023/08/07 04:45:01 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// how to parse the arguments of echo
//

int	ft_echo(t_parsing_output *cmd)
{
	int	i;
	int	j;
	int nl;
	int	status;

	i = 1;
	nl = 0;
	status = 0;
	while (cmd->cmd[i])
	{
		if (ft_strncmp(cmd->cmd[i], "-n", 1) == 0)
		{
			j = 2;
			while (cmd->cmd[i][j] && cmd->cmd[i][j] == 'n')
				j++;
			if (!cmd->cmd[i][j])
			{
				nl = 1;
				i++;
				continue;
			}
		}
		ft_putstr_fd(cmd->cmd[i], cmd->fd_outfile);
		if (cmd->cmd[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (nl == 0)
		ft_putchar_fd('\n', cmd->fd_outfile);
	return (status);
}
