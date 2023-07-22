/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:22:46 by ibel-har          #+#    #+#             */
/*   Updated: 2023/03/25 08:34:41 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	wait_for_childs(t_vars vars, int *status)
{
	waitpid(vars.pid, status, 0);
	while (wait(NULL) != -1)
		;
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	int		status;

	check_args_bonus(argc, argv, &vars);
	vars.std_in = dup(0);
	if (vars.std_in == -1)
		pfd_err_msg("Dup");
	if (vars.infile != -1)
	{
		if (dup2(vars.infile, 0) == -1)
			pfd_err_msg("Dup2");
		close(vars.infile);
	}
	if (!ft_strncmp(argv[1], "here_doc", 8) && ft_strlen(argv[1]) == 8)
		here_doc(argv, &vars);
	while (vars.count < vars.argc - 1)
	{
		run_ps(argv[vars.count], &vars, envp);
		vars.count++;
	}
	wait_for_childs(vars, &status);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
