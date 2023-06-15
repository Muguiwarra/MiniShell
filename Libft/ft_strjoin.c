/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:25:57 by nabboune          #+#    #+#             */
/*   Updated: 2022/10/25 23:44:30 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	ls1;
	size_t	ls2;
	size_t	i;
	int		j;

	if (!s1)
		return (0);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	i = ls1;
	j = 0;
	ptr = (char *)malloc(ls1 + ls2 + 1);
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s1, ls1 + 1);
	while (i < ls1 + ls2)
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}
