/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 20:43:41 by nabboune          #+#    #+#             */
/*   Updated: 2022/11/11 04:20:49 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	i;
	size_t	j;

	if (!dstsize && !dst)
		return (ft_strlen(src));
	dlen = ft_strlen(dst);
	if (dstsize <= dlen)
		return (dstsize + ft_strlen(src));
	i = 0;
	j = dlen;
	while (dstsize > dlen && src[i] && i < dstsize - dlen - 1)
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	return (dlen + ft_strlen(src));
}
