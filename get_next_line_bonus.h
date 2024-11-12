/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 02:39:43 by madelmen          #+#    #+#             */
/*   Updated: 2024/11/12 02:39:43 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define MAX_FD 1024

typedef struct s_fd_storage
{
    int     fd;
    char    *saved;
    struct s_fd_storage *next;
} t_fd_storage;

char			*get_next_line(int fd);
t_fd_storage	*get_or_create_fd_storage(int fd, t_fd_storage **storage_list);
char			*read_and_save(int fd, char *saved);
char			*ft_get_line(char **saved);

char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(const char *s1);
size_t			ft_strlen(const char *s);
char			*ft_strchr(const char *s, int c);
char			*ft_substr(char const *s, unsigned int start, size_t len);

#endif