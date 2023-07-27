/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 02:57:36 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/27 22:00:39 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_dlm_count(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str[0] == c)
		count++;
	while (str[i])
	{
		if (str[i] == c && (str[i + 1] == c || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count + i);
}

char	*add_char(char *str, char dlm, char to_add)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = (char *)malloc(sizeof(char) * (ft_dlm_count(str, dlm) + 1));
	while (str[i])
	{
		if (i == 0 && str[i] == dlm)
			new_str[j++] = to_add;
		if (str[i] == dlm && (str[i + 1] == dlm || str[i + 1] == '\0'))
		{
			new_str[j++] = dlm;
			new_str[j++] = to_add;
		}
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
