/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:57:58 by nabboune          #+#    #+#             */
/*   Updated: 2023/08/07 18:01:21 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pre_prompt(void)
{
	signal(SIGINT, ft_new_line);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSEGV, ft_new_line);
	g_glob.exit_status = 0;
	rl_on_new_line();
}

int	ft_dic_not_created(t_dic *dic, char *input)
{
	if (!dic)
	{
		ft_dprintf(2, "MiniShell-0.1: Not enough ressources\n");
		ft_ending_prompt(input);
		return (1);
	}
	return (0);
}

int	ft_check_dic_exit(t_dic *dic, char *input)
{
	if (ft_check_exit())
	{
		ft_ending_prompt(input);
		return (1);
	}
	ft_check_dic(dic);
	if (ft_check_exit())
	{
		ft_ending_prompt(input);
		return (1);
	}
	return (0);
}

int	ft_update(t_dic **dic, char *input)
{
	ft_update_00(dic);
	ft_check_dic(*dic);
	if (ft_check_exit())
	{
		ft_ending_prompt(input);
		return (1);
	}
	ft_update_01(dic);
	if (ft_check_exit())
	{
		ft_ending_prompt(input);
		return (1);
	}
	ft_update_02(dic);
	if (ft_check_exit())
	{
		ft_ending_prompt(input);
		return (1);
	}
	ft_update_03(dic);
	return (0);
}
