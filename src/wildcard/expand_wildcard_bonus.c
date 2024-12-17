/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:39:00 by hitran            #+#    #+#             */
/*   Updated: 2024/12/16 10:46:08 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strdup_error(char **result, int index)
{
	if (!result || !result[index])
	{
		free_array(result);
		return (print_malloc_error());
	}
	return (EXIT_SUCCESS);
}

void	concat_arrays(char ***array1, char *array2)
{
	int		len;
	char	**result;
	int		index;

	len = array_length(*array1);
	result = (char **)malloc((len + 2) * sizeof(char *));
	if (!result)
		return ;
	index = -1;
	while (++index < len)
	{
		result[index] = ft_strdup((*array1)[index]);
		if (strdup_error(result, index) == EXIT_FAILURE)
			return ;
	}
	result[len] = ft_strdup(array2);
	if (strdup_error(result, len) == EXIT_FAILURE)
		return ;
	result[len + 1] = NULL;
	free_array(*array1);
	*array1 = result;
}

char	**null_entry_return(char **matches, DIR *dir)
{
	if (matches)
		free_array(matches);
	closedir(dir);
	return (NULL);
}

char	**expand_wildcard(char *command, char **matches)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*entry_name;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry)
	{
		if ((entry->d_name[0] != '.' || command[0] == '.')
			&& is_match(entry->d_name, command))
		{
			entry_name = ft_strdup(entry->d_name);
			if (!entry_name)
				return (null_entry_return(matches, dir));
			concat_arrays(&matches, entry_name);
			free(entry_name);
			if (!matches)
				break ;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (matches);
}
