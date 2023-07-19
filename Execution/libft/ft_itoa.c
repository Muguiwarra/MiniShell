/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <ibel-har@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:26:32 by ibel-har          #+#    #+#             */
/*   Updated: 2022/11/06 05:11:14 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intlen(int nb)
{
	int	i;

	i = 1;
	while (nb / 10)
	{
		nb = nb / 10;
		i++;
	}
	if (nb < 0)
		return (i + 1);
	return (i);
}

static long	intrev(int nb, int len)
{
	long	newnb;
	int		num;

	newnb = 0;
	num = nb;
	while (len > 0)
	{
		newnb = (newnb * 10) + (num % 10);
		num /= 10;
		len--;
	}
	return (newnb);
}

static int	isneg(int nb)
{
	if (nb < 0)
		return (1);
	return (0);
}

char	*ft_itoa(int n)
{
	char	*dest;
	long	nb;
	int		i;
	int		len;

	i = 0;
	len = intlen(n);
	nb = intrev(n, len);
	if (isneg(n))
		nb = -1 * intrev(n, len - 1);
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (!dest)
		return (0);
	if (isneg(n))
		dest[i++] = '-';
	while (i < len)
	{
		dest[i++] = '0' + (nb % 10);
		nb = nb / 10;
	}
	dest[i] = '\0';
	return (dest);
}
