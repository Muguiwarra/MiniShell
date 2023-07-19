/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:23:25 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/19 08:08:42 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dputptr(int fd, unsigned long nb)
{
	int	i;

	i = 0;
	if (nb >= 0 && nb < 16)
	{
		if (nb >= 0 && nb < 10)
			i += ft_dputchar(fd, nb + 48);
		else if (nb >= 10 && nb < 16)
			i += ft_dputchar(fd, nb + 87);
	}
	else
	{
		i += ft_dputptr(fd, (nb / 16));
		i += ft_dputptr(fd, (nb % 16));
	}
	return (i);
}
