/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 06:26:17 by nabboune          #+#    #+#             */
/*   Updated: 2023/06/25 07:22:02 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_export(char *var)
{
	char	*val;
	int		i;

	i = 0;
	while (g_glob.env[i])
	{
		if (ft_strncmp(g_glob.env[i], var, ft_strlen(var)) == 0)
			return (g_glob.env[i] + ft_strlen(var));
		i++;
	}
	return (0);
}