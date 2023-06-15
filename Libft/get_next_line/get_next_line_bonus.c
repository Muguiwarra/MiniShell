/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabboune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:05:26 by nabboune          #+#    #+#             */
/*   Updated: 2022/12/25 17:23:48 by nabboune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_strjoin_with_null(char *s2)
{
	char	*ptr;
	int		i;

	ptr = malloc((ft_strlen_m(s2) + 1) * sizeof(char));
	if (!ptr)
		return (0);
	i = 0;
	while (s2[i])
	{
		ptr[i] = s2[i];
		i++;
	}
	ptr[i] = '\0';
	if (!*ptr)
	{
		free(ptr);
		return (0);
	}
	return (ptr);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ptr;

	if (!s1)
		return (ft_strjoin_with_null(s2));
	ptr = malloc((ft_strlen_m(s1) + ft_strlen_m(s2) + 1) * sizeof(char));
	if (ptr)
	{
		i = 0;
		j = 0;
		while (s1[i])
			ptr[j++] = s1[i++];
		i = 0;
		while (s2[i])
			ptr[j++] = s2[i++];
		ptr[j] = '\0';
	}
	if (!ptr || !*ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (ptr);
}

static int	ft_read(int fd, char **line)
{
	char	*tmp;
	int		nl_index;
	int		got_read;
	char	*buf;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	got_read = 1;
	while (got_read > 0)
	{
		got_read = read(fd, buf, BUFFER_SIZE);
		if (got_read == -1)
			break ;
		buf[got_read] = '\0';
		tmp = *line;
		*line = ft_strjoin(*line, buf);
		ft_free(tmp);
		if (!*line)
			return (free(buf), -2);
		nl_index = ft_strchr_m(*line, '\n');
		if (nl_index == -1)
			continue ;
		break ;
	}
	ft_free(buf);
	return (nl_index);
}

char	*get_next_line(int fd)
{
	static char	*line[OPEN_MAX];
	char		*final_str;
	int			nl_index;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (line[fd])
			free(line[fd]);
		return (line[fd] = 0);
	}
	tmp = 0;
	nl_index = ft_read(fd, &line[fd]);
	if (nl_index == -2)
		return (0);
	if (nl_index == -1)
	{
		tmp = line[fd];
		line[fd] = 0;
		return (tmp);
	}
	tmp = line[fd];
	final_str = ft_substr_m(line[fd], 0, nl_index);
	line[fd] = ft_newline(line[fd], nl_index);
	return (free(tmp), final_str);
}
