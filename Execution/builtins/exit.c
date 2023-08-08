/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:33:28 by ibel-har          #+#    #+#             */
/*   Updated: 2023/08/08 05:40:40 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

unsigned long long	status_overflow(char *str, int *sing_store)
{
	int					i;
	int					sign;
	unsigned long long	res;

	i = 0;
	sign = 1;
	res = 0;
	if (!str[0])
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32 || str[i] == 48)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			sign = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + str[i++] - '0';
	}
	*sing_store = sign;
	return (res);
}

int	status_calculator(char *str)
{
	unsigned long long	res;
	unsigned long long	max;
	int					sign;
	int					status;

	res = status_overflow(str, &sign);
	max = 9223372036854775807;
	if ((sign == -1 && res > max + 1) || (sign == 1 && res > max))
		return (-1);
	else if (sign == -1 && res == max + 1)
		return (0);
	else
	{
		res = (long)res * sign;
		status = (int)(res % 256);
		return (status);
	}
}

int	is_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			i++;
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	status_setter(char *str)
{
	int	status;

	status = status_calculator(str);
	if (!is_digits(str) || status == -1)
	{
		if (g_glob.cmds_count == 1)
			ft_putstr_fd("exit\n", 1);
		ft_dprintf(2, "exit: %s: numeric argument required\n", str);
		status = 255;
	}
	return (status);
}

int	ft_exit(char **arg)
{
	int	status;
	int	len;

	status = 0;
	len = array_len(arg);
	if (len > 2 && !is_digits(arg[len - 1]))
	{
		ft_dprintf(2, "exit: too many arguments\n");
		return (-1);
	}
	else if (len > 2 && is_digits(arg[len - 1]))
	{
		ft_dprintf(2, "exit: %s: numeric argument required\n", arg[1]);
		return (255);
	}
	else if (len == 2)
		status = status_setter(arg[1]);
	else if (len == 1)
		status = g_glob.exit_stat;
	if (g_glob.cmds_count == 1)
		ft_putstr_fd("exit\n", 1);
	return (status);
}
