/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:43:25 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/08 00:09:35 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count && size > SIZE_MAX / count)
		return (0);
	ptr = (char *)ft_malloc(count * size, 1);
	if (!ptr)
		return (0);
	if (ptr)
		ft_bzero(ptr, count * size);
	return (ptr);
}
