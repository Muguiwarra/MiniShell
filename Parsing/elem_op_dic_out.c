/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_op_dic_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 00:53:07 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/01 16:53:52 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_file_err(t_dic *dic)
{
	ft_dprintf(2,"Minishell-0.1: %s: %s\n", dic->value, strerror(errno));
	g_glob.exit_status = UNSPECIFIED_ERROR;
}

int	ft_pipes(t_dic *dic)
{
	t_dic	*ptr;

	ptr = dic;
	while (dic)
	{
		ptr = dic;
		dic = dic->next;
	}
	return (ptr->pipe + 1);
}

int	ft_nb_infiles(t_dic *dic, int pipe)
{
	int	i;

	i = 0;
	while (dic)
	{
		if (dic->pipe == pipe && dic->key == INFILE)
			i++;
		dic = dic->next;
	}
	return (i);
}

int	ft_nb_outfiles(t_dic *dic, int pipe)
{
	int	i;

	i = 0;
	while (dic)
	{
		if (dic->pipe == pipe && dic->key == OUTFILE)
			i++;
		dic = dic->next;
	}
	return (i);
}

int	ft_nb_cmd(t_dic *dic, int pipe)
{
	int	i;

	i = 0;
	while (dic)
	{
		if (dic->pipe == pipe && dic->key == CMD)
			i++;
		dic = dic->next;
	}
	return (i);
}
