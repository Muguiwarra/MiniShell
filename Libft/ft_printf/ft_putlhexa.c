/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlhexa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:20:24 by nabboune          #+#    #+#             */
/*   Updated: 2022/11/10 02:05:16 by nabboune         ###   ########.fr       */
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

static char	*ft_allocation(unsigned int nb, char *ptr)
{
	int				i;
	unsigned int	div;

	i = 1;
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

char	*ft_putlhexa(unsigned int nb)
{
	char			*lh;
	char			*conv;
	int				i;
	unsigned int	div;
	unsigned int	mod;

	conv = NULL;
	lh = "0123456789abcdef";
	conv = ft_allocation(nb, conv);
	div = nb / 16;
	mod = nb % 16;
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
