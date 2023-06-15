/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 00:27:50 by nabboune          #+#    #+#             */
/*   Updated: 2022/10/24 00:33:00 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	if (str[i] == (char)c)
		return ((char *)str + i);
	while (str[i])
	{
		i++;
		if (str[i] == (char)c)
			return ((char *)str + i);
	}
	return (0);
}
