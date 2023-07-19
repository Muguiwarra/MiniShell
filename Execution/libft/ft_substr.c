/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:57:01 by ibel-har          #+#    #+#             */
/*   Updated: 2023/02/22 17:50:45 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	slen;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	slen = ft_strlen((char *)s);
	if (start > slen || !len)
		return (ft_strdup(""));
	if (len > ft_strlen((char *)s + start))
		len = slen - start;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (0);
	while (i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
