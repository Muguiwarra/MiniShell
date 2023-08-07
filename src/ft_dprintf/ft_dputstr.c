/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:28:38 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/19 08:08:55 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dputstr(int fd, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		j += ft_dputstr(fd, "(null)");
	else
	{
		while (str[i])
			j += ft_dputchar(fd, str[i++]);
	}
	return (j);
}
