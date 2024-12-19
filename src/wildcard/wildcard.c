/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:39:00 by hitran            #+#    #+#             */
/*   Updated: 2024/12/19 12:31:24 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_wildcard(char ***splitted, int pos, char **matches)
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

void	command_wildcard(char ***splitted)
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
			matches = expand_wildcard((*splitted)[index], NULL);
			if (!matches)
				continue ;
			if (!replace_wildcard(splitted, index, matches))
			{
				free_array(matches);
				continue ;
			}
			index += array_length(matches) - 1;
			free_array(matches);
		}
	}
}

int	redirect_wildcard(t_redirect *redirect)
{
	char	**matches;

	while (redirect)
	{
		if (!ft_strcmp(redirect->path, "*")
			|| inside_quotes(redirect->org_path))
			;
		else if (redirect->path && !inside_quotes(redirect->path)
			&& ft_strcmp(redirect->path, "*") && ft_strchr(redirect->path, '*'))
		{
			matches = expand_wildcard(redirect->path, NULL);
			if (!matches)
				return (EXIT_FAILURE);
			free(redirect->path);
			if (array_length(matches) != 1)
				redirect->path = ft_strdup("*");
			else
				redirect->path = ft_strdup(matches[0]);
			free_array(matches);
			if (!redirect->path)
				return (print_malloc_error());
		}
		redirect = redirect->next;
	}
	return (EXIT_SUCCESS);
}

int	wildcard(t_token *tokens, int size)
{
	int	index;

	index = 0;
	while (index < size)
	{
		if (tokens[index].type == CMD)
		{
			if (redirect_wildcard(tokens[index].redirect) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			if (tokens[index].cmd && !ft_strcmp(tokens[index].cmd, "$EMPTY"))
				return (EXIT_FAILURE);
			if (tokens[index].split_cmd)
				command_wildcard(&tokens[index].split_cmd);
		}
		index++;
	}
	return (EXIT_SUCCESS);
}
