/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 05:34:43 by marvin            #+#    #+#             */
/*   Updated: 2022/11/10 02:10:03 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_ndigit(unsigned int n)
{
	unsigned int	temp;
	int				j;

	j = 1;
	temp = n;
	while (temp / 10 > 9)
	{
		temp = temp / 10;
		j++;
	}
	j++;
	if (temp / 10 == 0)
		j--;
	return (j);
}

static char	*ft_pnbr(char *ptr, unsigned int n)
{
	int	j;
	int	k;

	j = ft_ndigit(n);
	k = j;
	while (n / 10 > 9)
	{
		ptr[j - 1] = n % 10 + '0';
		n = n / 10;
		j--;
	}
	ptr[j - 1] = n % 10 + '0';
	if (n / 10 != 0)
		ptr[j - 2] = n / 10 + '0';
	ptr[k] = '\0';
	return (ptr);
}

char	*ft_putunsi(unsigned int n)
{
	char	*ptr;
	int		j;

	j = ft_ndigit(n);
	if (n == 0)
		ptr = (char *)malloc(2 * sizeof(char));
	else
		ptr = (char *)malloc((j + 1) * sizeof(char));
	if (!ptr)
		return (0);
	if (n == 0)
	{
		ptr[0] = '0';
		ptr[1] = '\0';
	}
	else
		ptr = ft_pnbr(ptr, n);
	return (ptr);
}
