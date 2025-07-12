/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matmagal <matmagal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:43:54 by matmagal          #+#    #+#             */
/*   Updated: 2025/07/10 15:05:12 by matmagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_fd(int fd, char *buffer)
{
	char	*buffer_rd;
	int		bytes_rd;

	buffer_rd = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer_rd)
		return (NULL);
	bytes_rd = 1;
	while (bytes_rd != 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_rd = read(fd, buffer_rd, BUFFER_SIZE);
		if (bytes_rd == -1)
		{
			free(buffer_rd);
			return (NULL);
		}
		buffer_rd[bytes_rd] = 0;
		buffer = ft_strjoin(buffer, buffer_rd);
	}
	free(buffer_rd);
	return (buffer);
}

char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer)
		return (NULL);
	if (buffer[i] == '\n')
	{
		line = malloc(sizeof(char) * 2);
		if (!line)
			return (NULL);
		line[0] = '\n';
		line[1] = 0;
		return (line);
	}
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_strldup(buffer, i);
	return (line);
}

char	*ft_next_line(char *buffer)
{
	char	*next_line;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	next_line = malloc(sizeof(char) * ft_strlen(buffer) - i + 1);
	if (!next_line)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		next_line[j++] = buffer[i++];
	next_line[j] = 0;
	free (buffer);
	return (next_line);
}

char *get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read_fd(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);
	buffer = ft_next_line(buffer);
	return (line);
}
