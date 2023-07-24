/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:22:46 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/23 21:19:46 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	wait_for_childs(t_vars vars, int *status)
{
	waitpid(vars.pid, status, 0);
	while (wait(NULL) != -1)
		;
}

int	exec(int argc, char **argv, char **envp)
{
	t_vars	vars;
	int		status;

	vars.std_in = dup(0);
	if (vars.std_in == -1)
		pfd_err_msg("Dup");
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
