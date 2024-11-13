/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:06:59 by madelmen          #+#    #+#             */
/*   Updated: 2024/11/13 12:06:59 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (fd >= 0 && fd < OPEN_MAX && buffer[fd])
		{
			free(buffer[fd]);
			buffer[fd] = NULL;
		}
		return (NULL);
	}
	buffer[fd] = read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_line(buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = ft_next(buffer[fd]);
	return (line);
}

char	*read_file(int fd, char *str)
{
	char	*temp;
	char	*buffer;
	int		byte_read;

	if (!str)
		str = ft_calloc(1, 1);
	if (!str)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (free(str), NULL);
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
			return (free(buffer), free(str), NULL);
		buffer[byte_read] = '\0';
		temp = ft_strjoin(str, buffer);
		free(str);
		str = temp;
		if (!str || ft_strchr(buffer, '\n'))
			break ;
	}
	return (free(buffer), str);
}

char	*ft_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] && str[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*ft_next(char *str)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (free(str), NULL);
	line = ft_calloc((ft_strlen(str) - i + 1), sizeof(char));
	if (!line)
		return (free(str), NULL);
	i++;
	j = 0;
	while (str[i])
		line[j++] = str[i++];
	return (free(str), line);
}
