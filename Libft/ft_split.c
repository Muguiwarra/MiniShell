/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 01:32:10 by marvin            #+#    #+#             */
/*   Updated: 2022/10/24 00:32:53 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nstr(char const *s, char c)
{
	size_t	i;
	int		nc;

	i = 0;
	nc = 0;
	if (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if ((s[i] == c && s[i - 1] != c) || (s[i] != c && !s[i + 1]))
			nc++;
		i++;
	}
	return (nc);
}

static void	ft_strnptr(char **ptr, char const *s, size_t l, char c)
{
	size_t	i;
	int		j;
	int		ls;

	i = 0;
	j = 0;
	if (s[i] == c)
		i++;
	while (i < l)
	{
		ls = 0;
		while (s[i] && s[i] != c)
		{
			ls++;
			i++;
		}
		if (s[i - 1] != c)
		{
			ptr[j++] = (char *)malloc((ls + 1) * sizeof(char));
			if (!ptr[j - 1])
				return ;
		}
		if (s[i] != '\0')
			i++;
	}
}

static void	ft_fptr(char **ptr, char const *s, size_t l, char c)
{
	size_t	i;
	int		j;
	int		nc;
	int		ls;

	nc = ft_nstr(s, c);
	i = 0;
	j = 0;
	if (s[i] == c)
		i++;
	while (i < l && j < (nc + 2))
	{
		ls = 0;
		while (s[i] && s[i] != c)
			ptr[j][ls++] = s[i++];
		if (s[i - 1] != c)
			ptr[j++][ls] = '\0';
		i++;
	}
	ptr[j] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	l;
	int		nc;
	int		i;

	if (!s)
		return (0);
	nc = ft_nstr(s, c);
	l = ft_strlen(s);
	ptr = (char **)malloc((nc + 1) * sizeof(char *));
	if (!ptr)
		return (0);
	ft_strnptr(ptr, s, l, c);
	i = 0;
	while (i < nc)
	{
		if (!ptr[i])
			return (0);
		i++;
	}
	ft_fptr(ptr, s, l, c);
	return (ptr);
}
