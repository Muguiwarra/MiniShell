/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 21:13:07 by nabboune          #+#    #+#             */
/*   Updated: 2022/10/24 00:34:06 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	l;

	l = ft_strlen(str);
	while (l > 0)
	{
		if (str[l] == (char)c)
			return ((char *)str + l);
		l--;
	}
	if (str[l] == (char)c)
		return ((char *)str + l);
	return (0);
}
