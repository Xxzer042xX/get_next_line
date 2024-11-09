/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:17:06 by madelmen          #+#    #+#             */
/*   Updated: 2024/11/08 23:11:40 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_save(int fd, char *saved);
static char	*get_line(char **saved);

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	saved = read_and_save(fd, saved);
	if (!saved)
		return (NULL);
	if (!saved || *saved == '\0')
		return (NULL);
	line = get_line(&saved);
	return (line);
}

static char	*read_and_save(int fd, char *saved)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(saved, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), NULL);
		buffer[bytes_read] = '\0';
		if (saved == NULL)
			saved = ft_strdup(buffer);
		else
		{
			temp = ft_strjoin(saved, buffer);
			free(saved);
			saved = temp;
		}
	}
	return (free(buffer), saved);
}

static char	*get_line(char **saved)
{
	char	*line;
	char	*temp;
	size_t	i;

	i = 0;
	while ((*saved)[i] && (*saved)[i] != '\n')
		i++;
	if ((*saved)[i] == '\n')
	{
		line = ft_substr(*saved, 0, i + 1);
		temp = ft_strdup(*saved + i + 1);
		free(*saved);
		*saved = temp;
		if (**saved == '\0')
		{
			free(*saved);
			*saved = NULL;
		}
		return (line);
	}
	line = ft_strdup(*saved);
	free(*saved);
	*saved = NULL;
	return (line);
}
