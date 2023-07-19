/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <ibel-har@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:46:22 by ibel-har          #+#    #+#             */
/*   Updated: 2022/11/12 02:04:21 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	if (size && count > SIZE_MAX / size)
		return (0);
	i = count * size;
	ptr = malloc(count * size);
	if (!ptr)
		return (0);
	ft_memset(ptr, '\0', i);
	return (ptr);
}
