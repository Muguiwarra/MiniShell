/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 03:53:58 by nabboune          #+#    #+#             */
/*   Updated: 2023/07/23 17:19:40 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_dict	*page_new(int key, char *value, int pipe)
{
	t_dict	*new;

	new = (t_dict *)malloc(sizeof(t_dict));
	if (!new)
		return (NULL);
	new->key = key;
	if (!value)
		new->value = NULL;
	else
		new->value = ft_strdup(value);
	new->pipe = pipe;
	new->next = NULL;
	return (new);
}

t_dict	*dict_last(t_dict *dict)
{
	if (!dict)
		return (NULL);
	while (dict->next)
		dict = dict->next;
	return (dict);
}

void	dict_add_front(t_dict **dict, t_dict *new)
{
	if (new && dict)
	{
		if (*dict == NULL)
		{
			*dict = new;
			return ;
		}
		new->next = *dict;
		*dict = new;
	}
}

void	dict_add_back(t_dict **dict, t_dict *new)
{
	t_dict	*last;

	if (new && dict)
	{
		if (!*dict)
			*dict = new;
		else
		{
			last = dict_last(*dict);
			last->next = new;
		}
	}
}

void	dict_clear(t_dict **dict)
{
	t_dict	*tmp;

	if (!dict)
		return ;
	while (*dict)
	{
		tmp = (*dict)->next;
		free((*dict)->key);
		free((*dict)->value);
		free(*dict);
		*dict = tmp;
	}
}
