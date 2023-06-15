/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuhexa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:20:39 by nabboune          #+#    #+#             */
/*   Updated: 2022/11/10 01:05:01 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_putuhexa(unsigned int nb)
{
	char	*conv;
	int		i;

	i = 0;
	conv = ft_putlhexa(nb);
	while (conv[i])
	{
		conv[i] = ft_toupper(conv[i]);
		i++;
	}
	return (conv);
}
