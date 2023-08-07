/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dstrformat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:01:21 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/19 09:45:19 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	dstrformat(int fd, char c, va_list ptr)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_dputchar(fd, va_arg(ptr, int));
	else if (c == 's')
		count += ft_dputstr(fd, va_arg(ptr, char *));
	else if (c == 'p')
	{
		count += ft_dputstr(fd, "0x");
		count += ft_dputptr(fd, va_arg(ptr, unsigned long));
	}
	else if (c == 'x' || c == 'X')
		count += ft_dputhex(fd, va_arg(ptr, unsigned int), c);
	else if (c == 'd' || c == 'i')
		count += ft_dputnbr(fd, va_arg(ptr, int), 0);
	else if (c == 'u')
		count += ft_dputnbr(fd, va_arg(ptr, int), 1);
	return (count);
}
