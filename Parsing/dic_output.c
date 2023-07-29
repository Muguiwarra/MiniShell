/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dic_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:21:21 by nabboune          #+#    #+#             */
/*   Updated: 2023/07/29 19:44:01 by nabboune         ###   ########.fr       */
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

int	ft_infile(t_dic *dic, int in, int pipe)
{
	int		fd_infile;
	int		i;

	fd_infile = 0;
	i = 0;
	while (dic)
	{
		while (dic && dic->pipe == pipe)
		{
			if (dic->key == INFILE)
			{
				fd_infile = open(dic->value, O_RDONLY, 0644);
				if (fd_infile == -1)
				{
					perror(ft_strjoin("MiniShell : ", dic->value, 1));
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
		if (dic)
			dic = dic->next;
	}
	return (fd_infile);
}

int	ft_outfile(t_dic *dic, int out, int pipe)
{
	int		fd_outfile;
	int		i;

	fd_outfile = 1;
	i = 0;
	while (dic)
	{
		while (dic && dic->pipe == pipe)
		{
			if (dic->key == OUTFILE)
			{
				if (dic->special == APPEND)
				{
					fd_outfile = open(dic->value, O_APPEND | O_RDWR, 0644);
					if (fd_outfile == -1)
						fd_outfile = open(dic->value, O_CREAT | O_RDWR, 0644);
				}
				else
					fd_outfile = open(dic->value, O_CREAT | O_RDWR, 0644);
				if (fd_outfile == -1)
				{
					perror(ft_strjoin("MiniShell : ", dic->value, 1));
					g_glob.exit_status = UNSPECIFIED_ERROR;
					break ;
				}
				i++;
				if (i != out)
				{
					if (close(fd_outfile) == -1)
					{
						perror("MiniShell : ");
						g_glob.exit_status = UNSPECIFIED_ERROR;
						break ;
					}
				}
			}
			dic = dic->next;
		}
		if (dic)
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
		while (dic && dic->pipe != pipe)
			dic = dic->next;
		while (dic && dic->pipe == pipe)
		{
			while (dic && (dic->key == CMD || dic->key == SPACE))
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
		ft_addpipe_back(&output, ft_newpipe(ft_infile(dic, ft_nb_infiles(dic, p), p), ft_outfile(dic, ft_nb_outfiles(dic, p), p), ft_getcmd(dic, ft_nb_cmd(dic, p), p)));
		p++;
	}
	return (output);
}

