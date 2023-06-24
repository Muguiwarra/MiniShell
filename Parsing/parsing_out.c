/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 04:01:06 by nabboune          #+#    #+#             */
/*   Updated: 2023/06/24 04:01:34 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parsing_output	*ft_parsing_output(t_dic *dic)
{
	t_parsing_output	*out;
	t_dic				*ptr;
	int					op;
	int					i;
	int					j;

	out = ft_malloc(sizeof(t_parsing_output));
	i = 2;
	ptr = dic;
	while (ptr && ptr->key != PIPE)
	{
		op = ft_open_infile(ptr);
		if (ft_check_exit())
			continue;
		ptr = ptr->next;
	}
	while(dic)
	{
		if (dic->key == CMD)
		{
			ptr = dic->next;
			while (ptr && ptr->key != PIPE)
			{
				if (ptr->key == ARG)
					i++;
				ptr = ptr->next;
			}
			out->cmd = ft_malloc(i * sizeof(char *));
			if (!out->cmd)
			{
				g_glob.exit_status = UNSPECIFIED_ERROR;
				break ;
			}
			j = 0;
			while (dic && dic->key != PIPE)
			{
				if (ptr->key == CMD || ptr->key == ARG)
				{
					out->cmd[j] = dic->value;
					j++;
				}
				dic = dic->next;
			}
			out->cmd[j] = NULL;
		}
		// Fill Out The Nodes with the Infile fd...
	}
	return (out);
}
