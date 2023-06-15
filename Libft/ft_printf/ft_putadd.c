/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:20:14 by nabboune          #+#    #+#             */
/*   Updated: 2022/11/12 16:56:54 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_reverse(char *str)
{
	char	*ptr;
	int		slen;
	int		i;

	slen = ft_strlen(str);
	ptr = (char *)malloc(slen + 1);
	i = 0;
	while (slen > 0)
	{
		ptr[i] = str[slen - 1];
		i++;
		slen--;
	}
	ptr[i] = '\0';
	free(str);
	return (ptr);
}

static char	*ft_allocation(unsigned long nb, char *ptr)
{
	int				i;
	unsigned long	div;
	unsigned long	mod;

	i = 1;
	mod = nb % 16;
	div = nb / 16;
	while (div > 0)
	{
		i++;
		div = div / 16;
	}
	ptr = (char *)malloc(i + 1);
	if (!ptr)
		return (0);
	return (ptr);
}

static char	*ft_hexa(unsigned long nb)
{
	char			*lh;
	char			*conv;
	int				i;
	unsigned long	div;
	unsigned long	mod;

	conv = NULL;
	lh = "0123456789abcdef";
	conv = ft_allocation(nb, conv);
	mod = nb % 16;
	div = nb / 16;
	i = 0;
	while (div > 0)
	{
		conv[i++] = lh[mod];
		mod = div % 16;
		div = div / 16;
	}
	conv[i++] = lh[mod];
	conv[i] = '\0';
	conv = ft_reverse(conv);
	return (conv);
}

char	*ft_putadd(unsigned long add)
{
	char	*s1;
	char	*s2;
	int		i;
	int		j;
	int		l;

	i = 0;
	j = 0;
	s1 = ft_hexa(add);
	l = ft_strlen(s1) + 3;
	s2 = (char *)malloc(l * sizeof(char));
	s2[i++] = '0';
	s2[i++] = 'x';
	while (i < l)
		s2[i++] = s1[j++];
	free(s1);
	return (s2);
}
