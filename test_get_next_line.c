/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_next_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelmen <madelmen@student.42lausanne.ch   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:22:54 by madelmen          #+#    #+#             */
/*   Updated: 2024/11/08 16:22:54 by madelmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("test_file.txt", O_RDONLY);  // Ouvre le fichier en lecture seule
    if (fd == -1)
    {
        perror("Erreur d'ouverture du fichier");
        return (1);
    }

    char *line;
    // Lire chaque ligne du fichier jusqu'à la fin
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);  // Affiche la ligne lue
        free(line);  // Libère la mémoire allouée pour la ligne
    }

    close(fd);  // Ferme le fichier
    return (0);
}
