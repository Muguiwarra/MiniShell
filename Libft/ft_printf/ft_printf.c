/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:19:50 by nabboune          #+#    #+#             */
/*   Updated: 2022/11/20 00:05:39 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_do(char *s, int **count)
{
	if (!s)
	{
		ft_putstr_fd("(null)", 1);
		**count += 6;
		return ;
	}
	**count += ft_strlen(s);
	ft_putstr_fd(s, 1);
}

static void	ft_options(char o, va_list wut, int *count)
{
	char	*p;

	p = 0;
	if (o == 'c' || o == '%')
	{
		if (o == 'c')
			ft_putchar_fd(va_arg(wut, int), 1);
		else
			ft_putchar_fd('%', 1);
		*count = *count + 1;
	}
	else if (o == 's')
		ft_do(va_arg(wut, char *), &count);
	else if (o == 'p')
		ft_do(p = ft_putadd(va_arg(wut, unsigned long)), &count);
	else if (o == 'd' || o == 'i')
		ft_do(p = ft_itoa(va_arg(wut, int)), &count);
	else if (o == 'u')
		ft_do(p = ft_putunsi(va_arg(wut, unsigned long)), &count);
	else if (o == 'x')
		ft_do(p = ft_putlhexa(va_arg(wut, unsigned int)), &count);
	else if (o == 'X')
		ft_do(p = ft_putuhexa(va_arg(wut, unsigned int)), &count);
	free(p);
}

static int	ft_heart(char c, va_list wut, int *count, int *i)
{
	if (c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u' || c == 'x'
		|| c == 'X' || c == 'c' || c == '%')
	{
		ft_options(c, wut, count);
		*i += 2;
		return (1);
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (ft_heart(format[i + 1], args, &count, &i) == 1)
				continue ;
			else
				i++;
		}
		count++;
		ft_putchar_fd(format[i++], 1);
	}
	return (count);
}
