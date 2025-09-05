/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allali <allali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 21:13:18 by ilallali          #+#    #+#             */
/*   Updated: 2025/09/04 21:56:17 by allali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

size_t	ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	if (s == NULL)
		return (0);
	while (s[l])
	{
		l++;
	}
	return (l);
}

static char	*read_line(int fd, char *buffer)
{
	char	*tmp;
	ssize_t	bytes_read;

	bytes_read = 1;
	tmp = malloc((size_t)BUFFER_SIZE + 1);
	if (!tmp)
		return (free(buffer), NULL);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, tmp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(tmp);
			return (free(buffer), NULL);
		}
		tmp[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, tmp);
		if (!buffer || ft_strchr(buffer, '\n') != -1)
			break ;
	}
	free(tmp);
	return (buffer);
}

static char	*extract_line(char **buffer)
{
	char	*line;
	char	*remaining;
	size_t	i;

	if (!*buffer || **buffer == '\0')
		return (NULL);
	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	line = malloc(i + 1 + ((*buffer)[i] == '\n'));
	if (!line)
		return (NULL);
	ft_strlcpy(line, *buffer, i + 2);
	if ((*buffer)[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	if ((*buffer)[i] != '\0')
		remaining = ft_strdup(*buffer + i);
	else
		remaining = NULL;
	free (*buffer);
	*buffer = remaining;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(buffer), buffer = NULL, NULL);
	buffer = read_line(fd, buffer);
	if (!buffer || buffer[0] == '\0')
		return (free(buffer), buffer = NULL, NULL);
	line = extract_line(&buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
	}
	return (line);
}
