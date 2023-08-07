/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:04:27 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/31 03:58:19 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(void)
{
	char	*pwd;
	int		status;

	status = 0;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_dprintf(2, "pwd: error retrieving current directory \n");
		status = 1;
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	return (status);
}
