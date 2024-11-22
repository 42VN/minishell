/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 02:03:55 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/20 15:02:36 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "utils.h"

static int	double_size(char **line, size_t *size)
{
	char	*new_line;
	size_t	new_length;

	new_length = (*size) * 2;
	new_line = ft_calloc(new_length, sizeof(char));
	if (new_line == NULL)
		return (-1);
	ft_memcpy(new_line, *line, *size);
	free(*line);
	*line = new_line;
	*size = new_length;
	return (0);
}

static void	fill_line(char **line, size_t *size)
{
	size_t	pos;
	ssize_t	byte_read;

	pos = 0;
	while (1)
	{
		byte_read = read(STDIN_FILENO, *line + pos, 1);
		if (byte_read < 0 || (byte_read == 0 && pos == 0))
			break ;
		if (byte_read == 0 && pos > 0)
			continue ;
		if (*(*line + pos) == '\n' || *(*line + pos) == '\r')
		{
			*(*line + pos) = '\0';
			return ;
		}
		if (pos == *size - 1)
		{
			if (double_size(line, size) < 0)
				break ;
		}
		pos++;
	}
	free(*line);
	*line = NULL;
}

char	*ft_readline(const char *prompt)
{
	char	*line;
	size_t	size;

	write(STDOUT_FILENO, prompt, ft_strlen(prompt));
	errno = 0;
	size = 1024;
	line = (char *)ft_calloc(size, sizeof(char));
	if (line == NULL)
		return (NULL);
	fill_line(&line, &size);
	return (line);
}
