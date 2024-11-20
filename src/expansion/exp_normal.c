/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 23:58:11 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/20 13:48:30 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exp_normal(char **res, char *cmd, size_t *i)
{
	char	*str;
	char	*joined;
	size_t	start;

	start = *i;
	
	while (cmd[*i] && cmd[*i] != '\'' && cmd[*i] != '\"'
		&& cmd[*i] != '$' && cmd[*i] != '~')
	{
		(*i)++;
	}
	str = ft_substr(cmd, start, *i - start);
	if (!str)
		return (ft_free_null(res));
	joined = ft_strjoin(*res, str);
	free(str);
	if (!joined)
		return (ft_free_null(res));
	free(*res);
	*res = joined;
}

