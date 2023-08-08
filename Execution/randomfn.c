/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomfn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 23:14:13 by ibel-har          #+#    #+#             */
/*   Updated: 2023/08/08 05:18:59 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	randomy(void)
{
	int		fd;
	char	*buf;
	int		i;
	int		rand;

	fd = open("/dev/random", O_RDONLY);
	buf = get_next_line(fd);
	rand = 1;
	i = 0;
	while (buf[i] && i < 10)
		rand *= buf[i++];
	free(buf);
	close(fd);
	if (rand < 0)
		rand *= -1;
	return (rand);
}

char	*randfn(int N)
{
	int		i;
	int		randomizer;
	char	*filename;

	i = 0;
	randomizer = 0;
	filename = malloc(sizeof(char) * (N + 1));
	randomizer = randomy() % 10;
	while (i < N)
	{
		if (i == 0 || !(i % 4))
			filename[i] = (randomy() % 26) + 'A';
		else if (randomizer % 3 == 0)
			filename[i] = (randomy() % 26) + 'a';
		else if (randomizer % 3 == 1)
			filename[i] = (randomy() % 26) + 'A';
		else if (randomizer % 3 == 2)
			filename[i] = (randomy() % 10) + '0';
		i++;
	}
	filename[i] = '\0';
	return (filename);
}
