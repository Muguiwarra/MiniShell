/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <ibel-har@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:06:20 by ibel-har          #+#    #+#             */
/*   Updated: 2022/11/08 21:13:16 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	j;

	if (!dstsize)
		return (ft_strlen(src));
	dst_len = ft_strlen(dst);
	i = 0;
	j = dst_len;
	if (dstsize && dst_len < dstsize - 1)
	{	
		while (src[i] && dst_len + i < dstsize - 1)
			dst[j++] = src[i++];
		dst[j] = '\0';
	}
	if (dst_len >= dstsize)
		dst_len = dstsize;
	return (dst_len + ft_strlen(src));
}
