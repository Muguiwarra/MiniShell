/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 03:04:17 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/08 00:04:17 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_malloc(size_t size, int to_free)
{
	void	*ptr;
	t_list	*obj;

	ptr = malloc(size);
	if (!ptr)
		exit(UNSPECIFIED_ERROR);
	if (to_free == 1)
	{
		obj = malloc(sizeof(t_list));
		if (!obj)
			exit(UNSPECIFIED_ERROR);
		obj->content = ptr;
		obj->next = g_glob.allocations;
		g_glob.allocations = obj;
	}
	return (ptr);
}

void	ft_collect_garbadge(void)
{
	t_list	*ptr;
	t_list	*temp;

	ptr = g_glob.allocations;
	while (ptr)
	{
		temp = ptr;
		ptr = ptr->next;
		if (temp->content)
			free(temp->content);
		free(temp);
	}
	g_glob.allocations = NULL;
}
