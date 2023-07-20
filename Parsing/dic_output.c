/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dic_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:21:21 by nabboune          #+#    #+#             */
/*   Updated: 2023/07/20 12:38:34 by nabboune         ###   ########.fr       */
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

int	ft_infile(t_dic *dic, int in)
{
	int		fd_infile;
	int		p;
	int		i;

	fd_infile = 0;
	p = 0;
	i = 0;
	while (dic)
	{
		while (dic && dic->pipe == p)
		{
			if (dic->key == INFILE)
			{
				fd_infile = open(dic->value, O_RDONLY);
				if (fd_infile == -1)
				{
					perror(ft_strjoin("MiniShell : ", dic->value));
					p++;
					g_glob.exit_status = UNSPECIFIED_ERROR;
					break ;
				}
				i++;
				if (i != in)
				{
					if (close(fd_infile) == -1)
					{
						perror("MiniShell : ");
						g_glob.exit_status = UNSPECIFIED_ERROR;
						break ;
					}
				}
			}
			dic = dic->next;
		}
		p++;
		if (dic)
			dic = dic->next;
	}
	return (fd_infile);
}

t_parsing_output	*ft_parse_out(t_dic *dic)
{
	int					in;
	int					pipe;
	int					p;
	t_dic				*ptr;
	t_parsing_output	*out;

	ptr = dic;
	pipe = ft_pipes(dic);
	p = 0;
	out = NULL;
	while (p < pipe)
	{
		in = ft_nb_infiles(dic, p++);
		ft_addpipe_back(&out, ft_newpipe(ft_infile(dic, in), 0, NULL));
		printf("{%d}\n", out->fd_infile);
	}
	return (out);
}
