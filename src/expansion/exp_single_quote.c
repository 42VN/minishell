/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_single_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:39:09 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/17 01:48:27 by ktieu            ###   ########.fr       */
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

	start = *i;
	(*i)++;
	while (cmd[*i] && cmd[*i] != '\'')
		(*i)++;
	if (!cmd[*i])
		return (ft_free_null(res));
	(*i)++;
	str = ft_substr(cmd, start, *i - start);
	if (!str)
		return (ft_free_null(res));
	joined = ft_strjoin(*res, str);
	if (!joined)
	{
		free(str);
		return (ft_free_null(res));
	}
	free(*res);
	free(str);
	*res = joined;
}
