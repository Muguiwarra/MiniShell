/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <ibel-har@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 22:19:22 by ibel-har          #+#    #+#             */
/*   Updated: 2022/11/08 21:24:20 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_ch(const char *s, const char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	len;

	if (!s1 || !set)
		return (0);
	if ((!s1[0] && !set[0]) || !s1[0])
		return (ft_strdup(""));
	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] && find_ch(set, s1[i]))
		i++;
	while (s1[j] && find_ch(set, s1[j]))
		j--;
	if (i == ft_strlen(s1))
		return (ft_strdup(""));
	len = j - i + 1;
	return (ft_substr(s1, i, len));
}
