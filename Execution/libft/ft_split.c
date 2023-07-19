/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:25:28 by ibel-har          #+#    #+#             */
/*   Updated: 2023/02/16 17:14:50 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdbool.h>

static int	wordcount(char *s, char dlm)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != dlm && (s[i + 1] == dlm || s[i + 1] == '\0'))
			count++;
		i++;
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == dlm)
			s[i] = 0;
		i++;
	}
	return (count);
}

static char	**ar_clear(char **dst)
{
	int	i;

	i = 0;
	while (dst[i])
		free(dst[i++]);
	free(dst);
	dst = NULL;
	return (NULL);
}

static char	**wordalloc(char *str, char **dest, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < len)
	{
		if (!str[i])
			i++;
		else
		{
			dest[j] = ft_strdup(&str[i]);
			if (!dest[j])
				return (ar_clear(dest));
			else
			{
				j++;
				i += ft_strlen(&str[i]);
			}
		}
	}
	dest[j] = NULL;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	int		len;
	char	*dup;
	char	**str;

	if (!s)
		return (NULL);
	dup = ft_strdup(s);
	if (!dup)
		return (NULL);
	len = ft_strlen(dup);
	str = (char **)malloc((wordcount(dup, c) + 1) * sizeof(char *));
	if (!str)
		return (0);
	wordalloc(dup, str, len);
	free(dup);
	return (str);
}

// int main(int argc, char const *argv[])
// {
// 	if (argc != 2)
// 		return (0);
// 	char **spl = ft_split(argv[1], ' ');
// 	int i = 0;
// 	while (spl[i])
// 	{
// 		printf("%s\n", spl[i]);
// 		i++;
// 	}

// 	return 0;
// }