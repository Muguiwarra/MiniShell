/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 23:23:30 by nabboune          #+#    #+#             */
/*   Updated: 2023/06/15 23:54:26 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	ft_new_line(int signum)
{
	(void) signum;
	rl_on_new_line();
}

int	main(void)
{
	char* input;

	signal(SIGINT, &ft_new_line);
	while (1)
	{
		rl_on_new_line();
		input = readline("Enter a string: ");

		printf("You entered: %s\n", input);

		add_history(input);

		free(input);
	}

	return 0;
}