/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:19:34 by kruseva           #+#    #+#             */
/*   Updated: 2024/11/27 13:57:21 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*ptr;

	size = str_len(s1);
	ptr = malloc(size + 1);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, size + 1);
	return (ptr);
}

static char	*extract_line(char **saved, int newline_index)
{
	char	*line;

	line = malloc(newline_index + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, *saved, newline_index);
	line[newline_index] = '\0';
	return (line);
}

static char	*get_line(char **saved)
{
	int		newline_index;
	char	*line;
	char	*new_saved;

	newline_index = 0;
	if (!*saved)
		return (NULL);
	while ((*saved)[newline_index] && (*saved)[newline_index] != '\n')
		newline_index++;
	if ((*saved)[newline_index] == '\n')
		newline_index++;
	line = extract_line(saved, newline_index);
	if (!line)
		return (free(*saved), *saved = NULL, NULL);
	if ((*saved)[newline_index] == '\0')
		return (free(*saved), *saved = NULL, line);
	new_saved = ft_strdup(*saved + newline_index);
	if (!new_saved)
		return (free(line), free(*saved), *saved = NULL, NULL);
	free(*saved);
	*saved = new_saved;
	return (line);
}

int	handle_invalid_fd(int fd, char **saved)
{
	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE < 1 || read(fd, NULL, 0) < 0)
	{
		if (saved[fd])
		{
			free(saved[fd]);
			saved[fd] = NULL;
		}
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*saved[FD_MAX];
	char		*buffer;
	int			read_bytes;
	char		*temp;

	if ((handle_invalid_fd(fd, saved)) == 1)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(saved[fd]), saved[fd] = NULL, NULL);
	while (!str_chr(saved[fd], '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free(buffer), free(saved[fd]), saved[fd] = NULL, NULL);
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		temp = str_join(saved[fd], buffer);
		if (!temp)
			return (free(buffer), free(saved[fd]), saved[fd] = NULL, NULL);
		saved[fd] = temp;
	}
	free(buffer);
	return (get_line(&saved[fd]));
}

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

int main(void)
{
    int fd1, fd2, fd3;
    char *line1, *line2, *line3;

    // Open the files for reading
    fd1 = open("proba.txt", O_RDONLY);
    fd2 = open("proba1.txt", O_RDONLY);
    fd3 = open("variable_nls.txt", O_RDONLY);

    // Check if files are successfully opened
    if (fd1 < 0 || fd2 < 0 || fd3 < 0)
    {
        perror("Error opening file");
        if (fd1 >= 0) close(fd1);
        if (fd2 >= 0) close(fd2);
        if (fd3 >= 0) close(fd3);
        return 1;
    }

    // Read and display lines from the files interleaved
    printf("Reading lines from multiple file descriptors:\n");
    for (size_t i = 0; i < 6; i++) // Adjust number of iterations as needed
    {
        line1 = get_next_line(fd1);
        if (line1)
        {
            printf("fd1: %s\n", line1); // Add newline character
            free(line1);
        }
        else
        {
            printf("fd1: (null)\n");
        }

        line2 = get_next_line(fd2);
        if (line2)
        {
            printf("fd2: %s\n", line2); // Add newline character
            free(line2);
        }
        else
        {
            printf("fd2: (null)\n");
        }

        line3 = get_next_line(fd3);
        if (line3)
        {
            printf("fd3: %s\n", line3); // Add newline character
            free(line3);
        }
        else
        {
            printf("fd3: (null)\n");
        }
    }

    // Close the files
    close(fd1);
    close(fd2);
    close(fd3);

    return 0;
}