/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:54:43 by hitran            #+#    #+#             */
/*   Updated: 2025/02/17 15:54:46 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	malloc_error(char **s1, char *s2)
{
	if (s1 && *s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (s2)
		free(s2);
	ft_printf_fd(STDERR_FILENO, "minishell: memory allocation failed!\n");
	return (EXIT_FAILURE);
}

int	join_and_free(char **s1, char *s2)
{
	char	*res;
	char	*ptr;
	int		index;

	res = (char *)malloc(ft_strlen(*s1) + ft_strlen(s2) + 2);
	if (!res)
		return (malloc_error(s1, s2));
	ptr = res;
	index = 0;
	while (*s1 && (*s1)[index])
		*ptr++ = (*s1)[index++];
	index = 0;
	while (s2 && s2[index])
		*ptr++ = s2[index++];
	*ptr++ = '\n';
	*ptr = '\0';
	if (*s1)
		free(*s1);
	if (s2)
		free(s2);
	*s1 = res;
	return (EXIT_SUCCESS);
}

void	print_warning(char *path)
{
	if (path)
		ft_printf_fd(STDERR_FILENO, "minishell: warning: here-document at "
			"line 1 delimited by end-of-file (wanted `%s')\n", path);
}

int	heredoc_sigint(char *heredoc, char **path, char *line)
{
	if (heredoc)
		free(heredoc);
	if (line)
		free(line);
	if (path && *path)
		free(*path);
	*path = ft_strdup("");
	if (!*path)
		ft_printf_fd(STDERR_FILENO, "minishell: memory allocation failed!\n");
	return (EXIT_FAILURE);
}
