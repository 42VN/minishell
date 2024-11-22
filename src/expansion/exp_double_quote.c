/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_double_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:20:20 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/22 12:00:57 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_exp_double_quote(t_shell *shell, char **res, char *cmd, size_t *i)
{
	char	*str;
	char	*joined;
	size_t	start;

	(void)shell; //check
	start = *i;
	while (cmd[*i] && cmd[*i] != '\"' && cmd[*i] != '$')
		(*i)++;
	if (!cmd[*i])
		return (ft_free_null(res));
	str = ft_substr(cmd, start, *i - start);
	if (!str)
		return (ft_free_null(res));
	joined = ft_strjoin(*res, str);
	free(str);
	free(*res);
	*res = joined;
}

void	exp_double_quote(t_shell *shell, char **res, char *cmd, size_t *i)
{
	ft_join_quote(res, "\"");
	(*i)++;
	if (res)
	{
		while (cmd[*i] && cmd[*i] != '\"')
		{
			if (cmd[*i] == '$')
				exp_dollar_in_quote(shell, res, cmd, i);
			else
				ft_exp_double_quote(shell, res, cmd, i);
		}
	}
	(*i)++;
	ft_join_quote(res, "\"");
}
