/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:55:01 by mito              #+#    #+#             */
/*   Updated: 2024/06/22 12:57:42 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include "utils.h"
#include "constants.h"

static t_bool	is_match(const char *glob_pattern, const char *filename)
{
	char	*wildcard;
	char	*match;
	size_t	bytes;

	if (*glob_pattern == '\0')
		return (true);
	wildcard = find_symbol(glob_pattern, "*");
	if (wildcard == NULL)
	{
		if (ft_ends_with(filename, glob_pattern))
			return (true);
		return (false);
	}
	if (wildcard == glob_pattern)
		return (is_match(wildcard + 1, filename));
	bytes = wildcard - glob_pattern;
	match = ft_strnstr(filename, glob_pattern, bytes);
	if (match == NULL)
		return (false);
	return (is_match(wildcard + 1, match + bytes));
}

/**
 * If an error occurs, NULL is returned and errno is set to indicate the
 * error. To distinguish end of stream from an error, set errno to zero before
 * calling readdir() and then check the value of errno if NULL is returned.
*/
static int	fill(t_list *match_list, DIR *dir, const char *glob_pattern)
{
	struct dirent	*entry;
	char			*name;

	errno = 0;
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (
			is_match(glob_pattern, entry->d_name)
			&& !ft_starts_with(entry->d_name, ".")
		)
		{
			name = ft_strdup(entry->d_name);
			if (name == NULL || ft_list_push(match_list, name) < 0)
				return (free(name), -1);
		}
	}
	if (errno)
		return (perror("minishell: readdir"), -1);
	return (0);
}

static int	find_matches(t_list *match_list, const char *glob_pattern)
{
	char	buffer[PATH_MAX];
	DIR		*dir;

	if (getcwd(buffer, sizeof(buffer)) == NULL)
		return (perror("minishell: getcwd"), -1);
	dir = opendir(buffer);
	if (dir == NULL)
		return (perror("minishell: opendir"), -1);
	if (fill(match_list, dir, glob_pattern) < 0)
		return (-1);
	if (closedir(dir) < 0)
		return (perror("minishell: closedir"), -1);
	return (0);
}

/**
 * Check if a given string has wildcard and replace string with new one that
 * satisfies wildcard pattern.
 *
 * If no match content is found, this function does not update the given string.
 *
*/
t_list	*expand_wildcard(char *str)
{
	t_list	*match_list;

	match_list = ft_list(0);
	if (match_list == NULL)
		return (NULL);
	if (find_symbol(str, "*") == NULL)
		return (match_list);
	if (find_matches(match_list, str) < 0)
	{
		ft_list_clear(&match_list, free);
		return (NULL);
	}
	return (match_list);
}
