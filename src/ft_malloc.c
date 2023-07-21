/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 03:04:17 by nabboune          #+#    #+#             */
/*   Updated: 2023/07/21 17:25:53 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_malloc(size_t size, int i)
{
	void	*ptr;
	t_list	*obj;

	ptr = malloc(size);
	if (!ptr)
		exit(UNSPECIFIED_ERROR);
	if (i == 1)
	{
		obj = malloc(sizeof(t_list));
		if (!obj)
			exit(UNSPECIFIED_ERROR);
		obj->content = ptr;
		obj->next = g_glob.allocations;
		g_glob.allocations = obj;
	}
	return(ptr);
}

void	ft_collect_garbadge()
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
