/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:35:57 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/15 10:52:24 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft.h"

static char	*init_line(char *static_buff, int *eol_index)
{
	size_t	len;
	char	*line;

	len = 0;
	while (static_buff[len] && static_buff[len] != '\n')
		len++;
	len++;
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	ft_memcpy(line, static_buff, len);
	line[len] = '\0';
	if (len > 0 && line[len - 1] == '\n')
		*eol_index = len - 1;
	return (line);
}

static size_t	find_eol_symbol(char *line)
{
	size_t	i;

	i = 0;
	if (!line)
		return (-1);
	while (i < BUFFER_SIZE)
	{
		if (line[i] == '\n' || line[i] == '\0')
			return (i + 1);
		i++;
	}
	return (i);
}

static char	*extract_line(
	char *line,
	char *static_buff,
	int *eol_index,
	int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	read_bytes;
	size_t	line_size;

	while (*eol_index == -1)
	{
		ft_bzero(buffer, (BUFFER_SIZE + 1));
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(line);
			ft_bzero(static_buff, (BUFFER_SIZE + 1));
			return (NULL);
		}
		line_size = find_eol_symbol(buffer);
		ft_strlcpy_gnl(static_buff, &buffer[line_size], (BUFFER_SIZE + 1));
		buffer[line_size] = '\0';
		line = ft_strjoin_gnl(line, buffer, eol_index);
		if (read_bytes == 0)
		{
			ft_bzero(static_buff, BUFFER_SIZE + 1);
			break ;
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	static_buff[BUFFER_SIZE + 1];
	char		*line;
	int			eol_index;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	eol_index = -1;
	line = init_line(static_buff, &eol_index);
	if (!line)
		return (NULL);
	ft_strlcpy_gnl(static_buff, &static_buff[eol_index + 1], BUFFER_SIZE + 1);
	line = extract_line(line, static_buff, &eol_index, fd);
	if (!line || line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
