/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 03:53:58 by nabboune          #+#    #+#             */
/*   Updated: 2023/07/23 20:26:48 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	consicutiv_count(char *line, char c, int ocur)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] && count < ocur)
	{
		if ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
		{
			i++;
			continue ;
		}
		else if (line[i] == c)
			count++;
		else
			count = 0;
		i++;
	}
	if (count == ocur)
		return (1);
	return (0);
}

int consicutive_chars(char *line, char c, char d)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == c && line[i + 1] == d)
			return (1);
		i++;
	}
	return (0);
}

int	pipe_error(char *line)
{
	int	i;

	if (line[0] == '|' || line[ft_strlen(line) - 1] == '|')
		return (1);
	else if (check_consicutiv(line, '|', 2))
		return (1);
	while (line[i])
	{
		if (line[i] == '>' && line[i + 1] == '|')
			return (1);
		else if (line[i] == '<' && line[i + 1] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	redire_error(char *line)
{
	int	i;

	i = 0;
	if (check_consicutiv(line, '<', 3) || check_consicutiv(line, '>', 3))
		return (1);
	while (line[i])
	{
		i++;
	}
	return (0);
}

int	main(void)
{
	char	*line = "echo $HOME | | $USER";
	int ocur	= 2;
	if (pipe_error(line))
		printf("true\n");
	else
		printf("false\n");
	return (0);
}
