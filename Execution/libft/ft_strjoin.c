/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:37:16 by ibel-har          #+#    #+#             */
/*   Updated: 2023/02/22 17:51:29 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_join;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (0);
	str_join = (char *)malloc((ft_strlen((char *)s1) + ft_strlen((char *)s2)
				+ 1) * sizeof(char));
	if (!str_join)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str_join[i] = s1[i];
		i++;
	}
	while (s2[j])
		str_join[i++] = s2[j++];
	str_join[i] = '\0';
	return (str_join);
}
