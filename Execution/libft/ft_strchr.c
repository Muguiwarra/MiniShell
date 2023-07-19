/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <ibel-har@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:39:49 by ibel-har          #+#    #+#             */
/*   Updated: 2022/11/12 18:49:21 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	if ((char)c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[++i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
	}
	return (0);
}
