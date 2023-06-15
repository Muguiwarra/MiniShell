/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:38:38 by nabboune          #+#    #+#             */
/*   Updated: 2022/10/25 23:41:37 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_for_set(char a, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == a)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	j;

	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i])
	{
		if (check_for_set(s1[i], set) == 0)
			break ;
		i++;
	}
	if (!s1[i])
		return (ft_strdup(""));
	while (s1[j])
	{
		if (check_for_set(s1[j], set) == 0)
			break ;
		j--;
	}
	return (ft_substr(s1, i, j - i + 1));
}
