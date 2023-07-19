/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibel-har <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 17:24:11 by ibel-har          #+#    #+#             */
/*   Updated: 2023/07/12 09:28:10 by ibel-har         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	checkstor(char **stor, char **line)
{
	char	*temp;
	int		i;
	int		len;

	i = ft_strpchr(*stor, '\n');
	len = ft_strlen(*stor) - 1;
	if (i > -1)
	{
		temp = NULL;
		*line = ft_substr(*stor, 0, (i + 1));
		if (i < len)
			temp = ft_strdup(*stor + (i + 1));
		free(*stor);
		*stor = temp;
		return (1);
	}
	return (0);
}

void	retline(int res, char *rbuff, char **stor, char **line)
{
	char	*temp;
	int		i;

	i = ft_strpchr(rbuff, '\n');
	if (!(*stor))
	{
		*line = ft_substr(rbuff, 0, (i + 1));
		if (i < res - 1)
			*stor = ft_strdup(rbuff + (i + 1));
	}
	else
	{
		temp = ft_substr(rbuff, 0, (i + 1));
		*line = ft_strjoin(*stor, temp);
		free(temp);
		temp = NULL;
		if (i < res - 1)
			temp = ft_strdup(rbuff + (i + 1));
		free(*stor);
		*stor = temp;
	}
}

int	addline(int res, char *rbuff, char **stor, char **line)
{
	char	*temp;

	rbuff[res] = '\0';
	if (ft_strpchr(rbuff, '\n') > -1)
	{
		retline(res, rbuff, stor, line);
		return (1);
	}
	if (!(*stor))
		*stor = ft_strdup(rbuff);
	else
	{
		temp = ft_strjoin(*stor, rbuff);
		free(*stor);
		*stor = temp;
	}
	return (0);
}

int	readfunc(int fd, char *rbuff, char **stor, char **line)
{
	int	res;

	res = read(fd, rbuff, BUFFER_SIZE);
	while (res >= 0)
	{
		if (res == 0)
		{
			if (*stor)
			{
				*line = ft_strdup(*stor);
				free(*stor);
				*stor = NULL;
				return (0);
			}
			else
				return (0);
		}
		if (addline(res, rbuff, stor, line))
			return (1);
		res = read(fd, rbuff, BUFFER_SIZE);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*stor;
	char		*line;
	char		*rbuff;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (stor && checkstor(&stor, &line))
		return (line);
	rbuff = (char *)malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!rbuff)
		return (NULL);
	if (!readfunc(fd, rbuff, &stor, &line))
	{
		if (stor)
		{
			free(stor);
			stor = NULL;
		}
	}
	free(rbuff);
	return (line);
}
