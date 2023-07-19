/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:51:26 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/19 08:10:16 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	dchrchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (c);
		i++;
	}
	return (0);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	argptr;
	int		i;
	int		count;

	va_start(argptr, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (!format[i])
				break ;
			else if (dchrchr("cpsduixX", format[i]))
				count += dstrformat(fd, format[i], argptr);
			else
				count += ft_dputchar(fd, format[i]);
		}
		else
			count += ft_dputchar(fd, format[i]);
		i++;
	}
	va_end(argptr);
	return (count);
}
