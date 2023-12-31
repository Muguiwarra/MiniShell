/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:25:57 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/08 00:07:36 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2, int to_free)
{
	char	*ptr;
	size_t	ls1;
	size_t	ls2;
	size_t	i;
	int		j;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	i = ls1;
	j = 0;
	ptr = (char *)ft_malloc(ls1 + ls2 + 1, to_free);
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s1, ls1 + 1);
	while (i < ls1 + ls2)
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}
