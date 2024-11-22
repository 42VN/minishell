/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:39:00 by hitran            #+#    #+#             */
/*   Updated: 2024/11/22 23:16:34 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	concat_arrays(char ***array1, char **array2)
{
	int		len1;
	int		len2;
	char	**result;
	int		index;

	len1 = array_length(*array1);
	len2 = array_length(array2);
	result = (char **)malloc((len1 + len2 + 1) * sizeof(char *));
	if (!result)
		return ;
	index = -1;
	while (++index < len1)
	{
		result[index] = ft_strdup((*array1)[index]);
		if (!result[index])
		{
			free_array(result);
			return ;
		}
	}
	index = -1;
	while (++index < len2)
	{
		result[len1 + index] = ft_strdup(array2[index]);
		if (!result[len1 + index])
		{
			free_array(result);
			return ;
		}
	}
	result[len1 + len2] = NULL;
	free_array(*array1);
	*array1 = result;
}

char	**expand_wildcard(char *command)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;

	matches = NULL;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	while ((entry = readdir(dir)))
	{
		if (entry->d_name[0] != '.' && is_match(entry->d_name, command))
		{
			char *entry_name[2] = {ft_strdup(entry->d_name), NULL};
			if (!entry_name[0])
			{
				free_array(matches);
				closedir(dir);
				return (NULL);
			}
			concat_arrays(&matches, entry_name);
			free(entry_name[0]);
			if (!matches)
				break ;
		}
	}
	closedir(dir);
	return (matches);
}

int replace_wildcard(char ***splitted, int pos, char **matches)
{
	int		new_size;
	int		splitted_size;
	int		matches_size;
	char	**new_array;
	int		index;

	splitted_size = array_length(*splitted);
	matches_size = array_length(matches);
	new_size = splitted_size - 1 + matches_size;
	new_array = malloc((new_size + 1) * sizeof(char *));
	if (!new_array)
		return (0);
	index = -1;
	while (++index < pos)
		new_array[index] = ft_strdup((*splitted)[index]);
	index = -1;
	while (++index < matches_size)
		new_array[pos + index] = ft_strdup(matches[index]);
	index = pos;
	while (++index < splitted_size)
		new_array[matches_size + index - 1] = ft_strdup((*splitted)[index]);
	new_array[new_size] = NULL;
	free_array(*splitted);
	*splitted = new_array;
	return (1);
}

int	inside_quotes(char *str)
{
	char	quote;
	int		len;

	len = ft_strlen(str);
	quote = str[0];
	if ((quote == '\'' || quote == '\"') && len > 1 && str[len -1] == quote)
		return (1);
	return (0);
}

void command_wildcard(char ***splitted)
{
	int		index;
	char	**matches;

	index = -1;
	while ((*splitted)[++index])
	{
		if (inside_quotes((*splitted)[index]))
			continue ;
		if (ft_strchr((*splitted)[index], '*'))
		{
			matches = expand_wildcard((*splitted)[index]);
			if (!matches)
				return ;
			if (!replace_wildcard(splitted, index, matches))
			{
				free_array(matches);
				return ;
			}
			index += array_length(matches) - 1;
			free_array(matches);
		}
	}
}


void redirect_wildcard(t_redirect *redirect)
{
	char	**matches;

	while (redirect)
	{
		// printf("path = %s\n", redirect->path);
		if (redirect->path && ft_strcmp(redirect->path, "*") && ft_strchr(redirect->path, '*'))
		{
			matches = expand_wildcard(redirect->path);
			if (!matches)
				return ;
			free(redirect->path);
			if (array_length(matches) != 1)
				redirect->path = ft_strdup("*"); //check
			else
				redirect->path = ft_strdup(matches[0]); //check
			free_array(matches);
		}
		redirect = redirect->next;
	}
}

int	wildcard(t_token *tokens, int size)
{
	int	index;

	index = 0;
	while (index < size)
	{
		if (tokens[index].type == CMD)
		{
			redirect_wildcard(tokens[index].redirect);
			if (tokens[index].cmd && !ft_strcmp(tokens[index].cmd, "$EMPTY"))
				return (EXIT_FAILURE);
			if (tokens[index].cmd && tokens[index].split_cmd)
				command_wildcard(&tokens[index].split_cmd);
		}
		index++;
	}
	return (EXIT_SUCCESS);
}
