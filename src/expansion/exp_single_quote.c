/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_single_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:39:09 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/17 00:32:41 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Expansion string for single quotes is treated as literal string
 * 
 * Description:
 * 
 * -	No backslash handled 
 */
void	exp_single_quote(char **res, char *cmd, size_t *i)
{
	char	*str;
	char	*joined;
	size_t	start;

	start = *i + 1; // Skip the opening single quote
	(*i)++;
	while (cmd[*i] && cmd[*i] != '\'')
		(*i)++;
	if (!cmd[*i]) // No closing quote found
		return (ft_free_null(res));
	str = ft_substr(cmd, start, *i - start); // Extract content between quotes
	if (!str)
		return (ft_free_null(res));
	joined = ft_strjoin(*res, str); // Concatenate with the current result
	if (!joined)
	{
		free(str);
		return (ft_free_null(res));
	}
	free(*res);
	free(str);
	*res = joined;
	(*i)++; // Skip the closing single quote
}
