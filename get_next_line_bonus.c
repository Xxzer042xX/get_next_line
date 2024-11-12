/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 02:39:18 by madelmen          #+#    #+#             */
/*   Updated: 2024/11/12 03:43:41 by madelmen         ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_fd_storage	*get_or_create_fd_storage(int fd, t_fd_storage **storage_list);
char			*read_and_save(int fd, char *saved);
char			*ft_get_line(char **saved);

// Fonction principale pour obtenir la prochaine ligne
char	*get_next_line(int fd)
{
	static t_fd_storage	*storage_list;
	t_fd_storage		*fd_context;
	t_fd_storage		*prev;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	fd_context = get_or_create_fd_storage(fd, &storage_list);
	if (!fd_context)
		return (NULL);
	fd_context->saved = read_and_save(fd, fd_context->saved);
	if (!fd_context->saved || *fd_context->saved == '\0')
	{
		if (fd_context == storage_list)
			storage_list = fd_context->next;
		else
		{
			prev = storage_list;
			while (prev->next != fd_context)
				prev = prev->next;
			prev->next = fd_context->next;
		}
		free(fd_context->saved);
		free(fd_context);
		return (NULL);
	}
	line = ft_get_line(&fd_context->saved);
	return (line);
}

t_fd_storage	*get_or_create_fd_storage(int fd, t_fd_storage **storage_list)
{
	t_fd_storage	*current;
	t_fd_storage	*new_node;

	current = *storage_list;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	new_node = malloc(sizeof(t_fd_storage));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->saved = NULL;
	new_node->next = *storage_list;
	*storage_list = new_node;
	return (new_node);
}

// Fonction pour lire et sauvegarder
char	*read_and_save(int fd, char *saved)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		free(saved);
		return (NULL);
	}
	bytes_read = 1;
	while (!ft_strchr(saved, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), free(saved), NULL);
		buffer[bytes_read] = '\0';
		if (saved == NULL)
			saved = ft_strdup(buffer);
		else
		{
			temp = ft_strjoin(saved, buffer);
			free(saved);
			if (!temp)
				return (free(buffer), NULL);
			saved = temp;
		}
	}
	if (!saved)
		return (free(buffer), NULL);
	return (free(buffer), saved);
}

// Fonction pour extraire une ligne de `saved`
char	*ft_get_line(char **saved)
{
	char	*line;
	char	*temp;
	size_t	i;

	if (!saved)
		return (NULL);
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
