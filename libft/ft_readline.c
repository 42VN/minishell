/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:25:28 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/12 15:49:16 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static size_t	ft_rl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

static char	*ft_rl_strjoin(char *s1, char *s2)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;

	if (!s1)
		len1 = 0;
	else
		len1 = ft_strlen(s1);
	len2 = ft_rl_strlen(s2);
	new_str = (char *)malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	if (s1)
		ft_strlcpy(new_str, s1, len1 + 1);
	ft_strlcpy(new_str + len1, s2, len2 + 1);
	free(s1);
	return (new_str);
}

/**
 * Handler which handle the read() function for ft_readline
 * @returns
 * - (-1)	:	error
 * 
 * - (0)	:	no byte read
 * 
 * - (1)	:	success
 */
static int	ft_read_handler(int fd, char *buffer, char *result)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		ft_printf_fd(2, "ft_readline: read error\n");
		free(result);
		return (-1);
	}
	else if (bytes_read == 0)
	{
		return (0);
	}
	return (1);
}

char	*ft_readline(int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*result;
	int		status;
	int		eol;

	result = NULL;
	eol = 0;
	status = 0;
	while (!eol)
	{
		ft_memset(buffer, 0, BUFFER_SIZE + 1);
		status = ft_read_handler(fd, buffer, result);
		if (status == 0)
			break ;
		else if (status == -1)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			eol = 1;
		result = ft_rl_strjoin(result, buffer);
		if (!result)
			return (NULL);
	}
	return (result);
}
