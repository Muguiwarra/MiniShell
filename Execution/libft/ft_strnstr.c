/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <ibel-har@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:33:20 by ibel-har          #+#    #+#             */
/*   Updated: 2022/11/11 16:41:27 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!needle[i])
		return ((char *)haystack);
	else if (needle[i] && len)
	{
		while (haystack[i] != '\0' && i < len)
		{
			j = 0;
			if (haystack[i] == needle[j])
			{
				while (((i + j) < len) && haystack[i + j] == needle[j])
				{
					j++;
					if (needle[j] == '\0')
						return ((char *)(haystack + i));
				}
			}
		i++;
		}
	}
	return (0);
}
