/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dic_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:21:21 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/08 04:23:26 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_heredoc_fd(t_dic *dic, int nb, int *j)
{
	int	fd_heredoc;

	fd_heredoc = 0;
	fd_heredoc = here_doc(dic->next->value);
	if (fd_heredoc == -1)
		return (ft_file_err(dic), -1);
	(*j)++;
	if (*j != nb)
		if (close(fd_heredoc) == -1)
			return (ft_file_err(dic), fd_heredoc);
	return (fd_heredoc);
}

int	ft_infile(t_dic *dic, int in, int pipe)
{
	int	fd_infile;
	int	i;
	int	j;
	int	nb_heredoc;

	fd_infile = 0;
	i = 0;
	j = 0;
	nb_heredoc = ft_nb_heredoc(dic, pipe);
	while (dic && dic->pipe != pipe)
		dic = dic->next;
	while (dic && dic->pipe == pipe)
	{
		if (dic->key == INFILE)
			fd_infile = ft_infile_fd(dic, in, &i);
		else if (dic->key == HEREDOC)
			fd_infile = ft_heredoc_fd(dic, nb_heredoc, &j);
		dic = dic->next;
	}
	return (fd_infile);
}

int	ft_outfile(t_dic *dic, int out, int pipe)
{
	int	fd_outfile;
	int	i;

	fd_outfile = 1;
	i = 0;
	while (dic && dic->pipe != pipe)
		dic = dic->next;
	while (dic && dic->pipe == pipe)
	{
		if (dic->key == OUTFILE)
			fd_outfile = ft_outfile_fd(dic, out, &i);
		dic = dic->next;
	}
	return (fd_outfile);
}

char	**ft_getcmd(t_dic *dic, int nb_cmd, int pipe)
{
	char	**cmd;
	int		i;

	cmd = ft_malloc((nb_cmd + 1) * sizeof(char *), 1);
	i = 0;
	while (dic)
	{
		while (dic && dic->pipe == pipe)
		{
			while (dic && (dic->key == CMD || dic->key == SPACES))
			{
				if (dic->key == CMD)
					cmd[i++] = dic->value;
				dic = dic->next;
			}
			if (i != 0)
				break ;
			dic = dic->next;
		}
		cmd[i] = NULL;
		if (dic)
			dic = dic->next;
	}
	return (cmd);
}

t_parsing_output	*ft_parse_out(t_dic *dic)
{
	int					pipe;
	int					p;
	t_dic				*ptr;
	t_parsing_output	*output;

	ptr = dic;
	pipe = ft_pipes(dic);
	p = 0;
	output = NULL;
	while (p < pipe)
	{
		ft_addpipe_back(&output,
			ft_newpipe(ft_infile(dic, ft_nb_infiles(dic, p), p),
				ft_outfile(dic, ft_nb_outfiles(dic, p), p),
				ft_getcmd(dic, ft_nb_cmd(dic, p), p)));
		p++;
	}
	return (output);
}
