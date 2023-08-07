/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:52:31 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/31 06:38:16 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int		ft_dprintf(int fd, const char *formatter, ...);
int		ft_dputstr(int fd, char *str);
int		ft_dputhex(int fd, unsigned int nb, char ca_se);
int		ft_dputptr(int fd, unsigned long nb);
int		ft_dputchar(int fd, unsigned char c);
int		ft_dputnbr(int fd, long nb, int isun);
int		dstrformat(int fd, char c, va_list ptr);

#endif