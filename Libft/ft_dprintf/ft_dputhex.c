/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputhex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:23:25 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/19 08:08:12 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dputhex(int fd, unsigned int nb, char ca_se)
{
	int	i;

	i = 0;
	if (nb >= 0 && nb < 16)
	{
		if (nb >= 0 && nb < 10)
			i += ft_dputchar(fd, nb + 48);
		else if ((nb >= 10 && nb < 16) && (ca_se == 'x'))
			i += ft_dputchar(fd, nb + 87);
		else if ((nb >= 10 && nb < 16) && (ca_se == 'X'))
			i += ft_dputchar(fd, nb + 55);
	}
	else
	{
		i += ft_dputhex(fd, (nb / 16), ca_se);
		i += ft_dputhex(fd, (nb % 16), ca_se);
	}
	return (i);
}
