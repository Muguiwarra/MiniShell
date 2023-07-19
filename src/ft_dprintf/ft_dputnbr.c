/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:31:40 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/19 08:08:32 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dputnbr(int fd, long nb, int isun)
{
	int	i;

	i = 0;
	if (isun)
		nb = (unsigned int)nb;
	else
		nb = (int)nb;
	if (nb >= 0 && nb < 10)
		i += ft_dputchar(fd, nb + 48);
	else if (nb == -2147483648)
		i += ft_dputstr(fd, "-2147483648");
	else if (nb < 0)
	{
		i += ft_dputchar(fd, '-');
		i += ft_dputnbr(fd, nb * -1, isun);
	}
	else
	{
		i += ft_dputnbr(fd, (nb / 10), isun);
		i += ft_dputnbr(fd, (nb % 10), isun);
	}
	return (i);
}
