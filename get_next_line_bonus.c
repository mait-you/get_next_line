/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:55:25 by mait-you          #+#    #+#             */
/*   Updated: 2024/11/21 15:31:54 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*reset_line_backup(char **line_b, char *line, int line_len)
{
	char	*new_line_b;

	new_line_b = ft_strdup(*line_b + line_len);
	if (!new_line_b)
		return (free(line), free(*line_b), (*line_b = NULL));
	free(*line_b);
	*line_b = new_line_b;
	return (line);
}

static char	*get_clean_line(char **line_b)
{
	int		line_len;
	char	*line;

	if (!**line_b)
	{
		free(*line_b);
		*line_b = NULL;
		return (NULL);
	}
	line_len = 0;
	while ((*line_b)[line_len] != '\n' && (*line_b)[line_len])
		line_len++;
	if ((*line_b)[line_len] == '\n')
		line_len++;
	line = ft_substr(*line_b, 0, line_len);
	if (!line)
		return (free(*line_b), (*line_b = NULL));
	if (!reset_line_backup(line_b, line, line_len))
		return (NULL);
	return (line);
}

static char	*get_line(int fd, char **line_b, char *buffer)
{
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read && !ft_strchr(*line_b, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(*line_b), (*line_b = NULL));
		if (bytes_read == 0 && *line_b == NULL)
			return (NULL);
		buffer[bytes_read] = '\0';
		*line_b = ft_strjoin(*line_b, buffer);
		if (!*line_b)
			return (NULL);
	}
	return (*line_b);
}

char	*get_next_line(int fd)
{
	static char	*line_b[OPEN_MAX];
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!get_line(fd, &line_b[fd], buffer))
		return (free(buffer), NULL);
	free(buffer);
	return (get_clean_line(&line_b[fd]));
}
