/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:51:40 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/27 22:00:39 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_parsing_output	*pars_new(char **cmd, int infile, int outfile)
{
	t_parsing_output	*pars;

	pars = (t_parsing_output *)malloc(sizeof(t_parsing_output));
	if (pars == NULL)
		return (NULL);
	pars->cmd = cmd;
	pars->fd_infile = infile;
	pars->fd_outfile = outfile;
	pars->next = NULL;
	return (pars);
}

void	pars_add_back(t_parsing_output **pars, t_parsing_output *new)
{
	t_parsing_output	*tmp;

	if (*pars == NULL)
	{
		*pars = new;
		return ;
	}
	tmp = *pars;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	print_parsing_output(t_parsing_output *pars)
{
	int i;
	int j;

	j = 1;
	while (pars)
	{
		i = 0;
		printf("############## node nb : %d ###########\n", j++);
		while (pars->cmd[i])
		{
			printf("%s\n", pars->cmd[i]);
			i++;
		}
		printf("fd_infile : %d\n", pars->fd_infile);
		printf("fd_outfile : %d\n", pars->fd_outfile);
		pars = pars->next;
	}
}

t_parsing_output *creat_cmds(char **argv)
{
	t_parsing_output *cmds;
	char **cmd;
	int i;

	i = 1;
	cmds = NULL;
	while (argv[i])
	{
		cmd = ft_split(*argv, ' ');
		pars_add_back(&cmds, pars_new(cmd, 0, 1));
		cmd = NULL;
		i++;
	}
	return (cmds);
}
