/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:19:34 by kruseva           #+#    #+#             */
/*   Updated: 2025/01/28 16:05:41 by kruseva          ###   ########.fr       */
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
