/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-you <mait-you@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 12:54:13 by mait-you          #+#    #+#             */
/*   Updated: 2024/11/18 15:44:09 by mait-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_memory(char *mem)
{
	if (mem)
		free(mem);
	return (NULL);
}

static char	*reset_line_backup(char **line_backup, char *new_line, int line_len)
{
	char	*new_line_backup;

	new_line_backup = ft_strdup(*line_backup + line_len);
	if (!new_line_backup)
	{
		new_line = free_memory(new_line);
		*line_backup = free_memory(*line_backup);
		return (NULL);
	}
	*line_backup = free_memory(*line_backup);
	*line_backup = new_line_backup;
	return (new_line);
}

static char	*get_clean_line(char **line_backup)
{
	int		line_len;
	char	*new_line;

	if (!*line_backup || !**line_backup)
	{
		*line_backup = free_memory(*line_backup);
		return (NULL);
	}
	line_len = 0;
	while ((*line_backup)[line_len] != '\n' && (*line_backup)[line_len])
		line_len++;
	if ((*line_backup)[line_len] == '\n')
		line_len++;
	new_line = ft_substr(*line_backup, 0, line_len);
	if (!new_line)
	{
		*line_backup = free_memory(*line_backup);
		return (NULL);
	}
	if (!reset_line_backup(line_backup, new_line, line_len))
		return (NULL);
	return (new_line);
}

static char	*get_line(int fd, char **line_backup, char *buffer)
{
	char	*tmp;
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read != 0 && !ft_strchr(*line_backup, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			*line_backup = free_memory(*line_backup);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		tmp = *line_backup;
		*line_backup = ft_strjoin(tmp, buffer);
		tmp = free_memory(tmp);
		if (!*line_backup)
			return (NULL);
	}
	return (*line_backup);
}

char	*get_next_line(int fd)
{
	static char	*line_backup;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	if (!line_backup)
		line_backup = ft_strdup("");
	if (!get_line(fd, &line_backup, buffer))
	{
		buffer = free_memory(buffer);
		return (NULL);
	}
	line = get_clean_line(&line_backup);
	buffer = free_memory(buffer);
	return (line);
}
