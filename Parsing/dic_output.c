/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dic_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:21:21 by nabboune          #+#    #+#             */
/*   Updated: 2023/07/19 22:05:31 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	ft_infiles(t_dic *dic, int pipe)
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

t_parsing_output	ft_parse_out(t_dic *dic)
{
	t_dic	*ptr;
	int		fd_in;
	int		*in;
	int		i;
	int		pipe;
	int		p;

	ptr = dic;
	pipe = ft_pipes(dic);
	i = 0;
	p = 0;
	in = ft_malloc(sizeof(int) * pipe);
	while (p < pipe)
		in[i++] = ft_infiles(dic, p++);
	i = 0;
	p = 0;
	while (ptr)
	{
		while (ptr && ptr->pipe == p)
		{
			if (ptr->key == INFILE)
			{
				fd_in = open(ptr->value, O_RDONLY);
				if (fd_in == -1)
				{
					// ft_dprintf(2, "MiniShell : %s : No such file or directory", ptr->value);
					perror("MiniShell : ");
					p++;
					g_glob.exit_status = UNSPECIFIED_ERROR;
					break ;
				}
				i++;
				if (i != in[p]);
					if (close(fd_in) == -1)
						perror("MiniShell : ");
			}
			ptr = ptr->next;
		}
	}
}
