/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:33:28 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/19 10:25:24 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// remember the global variable exit status
// void	exit_shell(t_global *global, char *arg)
// {
// 	long long int	nb;
// 	exit();
// }


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
	int 				status;

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

void	exit_shell(t_global *global, char *arg)
{
	int	status;

	(void) global;
	if (arg)
	{
		status = status_calculator(arg);
		if (status == -1)
			printf("exit: %s: numeric argument required\n", arg);
		else
		{
			ft_putstr_fd("exit\n", 2);
			exit(status);
		}
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
}