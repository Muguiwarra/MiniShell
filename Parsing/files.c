/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 04:04:06 by nabboune          #+#    #+#             */
/*   Updated: 2023/06/24 04:04:35 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		ft_open_infile(t_dic *dic)
{
	int	op;

	op = 0;
	while (dic && dic->key != PIPE)
	{
		if (dic->key == INFILE)
		{
			op = open(dic->value, O_RDONLY, 0777);
			if (op == -1)
			{
				perror(dic->value);
				g_glob.exit_status = UNSPECIFIED_ERROR;
				break ;
			}
			if (close(op) == -1)
			{
				perror(dic->value);
				g_glob.exit_status = UNSPECIFIED_ERROR;
				break ;
			}
		}
		dic = dic->next;
	}
	return (op);
}