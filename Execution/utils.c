/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 21:04:18 by ibel-har          #+#    #+#             */
/*   Updated: 2023/08/08 05:45:03 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	out_len(t_parsing_output *out)
{
	int	i;

	i = 0;
	while (out)
	{
		i++;
		out = out->next;
	}
	return (i);
}

void	ft_dup2(int fd, int std_fd)
{
	if (dup2(fd, std_fd) == -1)
		pfd_err_msg("Dup2");
	if (close(fd) == -1)
		pfd_err_msg("Close");
}

void	ft_dup(int std_fd)
{
	if (dup(std_fd) == -1)
		pfd_err_msg("Dup");
}
