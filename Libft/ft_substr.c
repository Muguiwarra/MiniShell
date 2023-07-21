/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:37:56 by nabboune          #+#    #+#             */
/*   Updated: 2023/07/21 17:35:50 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len, int i)
{
	char	*ptr;
	size_t	slen;

	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (start > slen)
		return (ft_strdup(""));
	if (len <= slen - start)
		ptr = (char *)ft_malloc(len + 1, i);
	else
	{
		ptr = (char *)ft_malloc(slen - start + 1, i);
		len = slen - start;
	}
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, (s + start), (len + 1));
	return (ptr);
}
