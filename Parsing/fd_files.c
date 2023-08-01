/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 02:42:53 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/01 02:43:30 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_infile_fd(t_dic *dic, int in, int *i)
{
	int	fd_infile;

	fd_infile = 0;
	fd_infile = open(dic->value, O_RDONLY, 0644);
	if (fd_infile == -1)
		return(ft_file_err(dic), 0);
	(*i)++;
	if (*i != in)
		if (close(fd_infile) == -1)
			return(ft_file_err(dic), fd_infile);
	return (fd_infile);
}

int	ft_outfile_fd(t_dic *dic, int out, int *i)
{
	int	fd_outfile;

	fd_outfile = 1;
	if (dic->special == APPEND)
	{
		fd_outfile = open(dic->value, O_APPEND | O_RDWR, 0644);
		if (fd_outfile == -1)
			fd_outfile = open(dic->value, O_CREAT | O_RDWR, 0644);
	}
	else
		fd_outfile = open(dic->value, O_CREAT | O_RDWR, 0644);
	if (fd_outfile == -1)
		return(ft_file_err(dic), 1);
	(*i)++;
	if (*i != out)
		if (close(fd_outfile) == -1)
			return(ft_file_err(dic), 1);
	return(fd_outfile);
}
