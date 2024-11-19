/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_double_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:20:20 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/19 15:37:56 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_exp_double_quote(t_shell *shell, char **res, char *cmd, size_t *i)
{
	char	*str;
	char	*joined;
	size_t	start;

	start = *i;
	while (cmd[*i] && cmd[*i] != '\"')
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

static void ft_join_quote(char **res)
{
	char	*joined;

	joined = ft_strjoin(*res, "\"");
	if (!joined)
		return (ft_free_null(res));
	free(*res);
	*res = joined;
}

void	exp_double_quote(t_shell *shell, char **res, char *cmd, size_t *i)
{
	ft_join_quote(res);
	(*i)++;
	if (res)
	{
		while (cmd[*i] != '\"')
		{
			if (cmd[*i] == '$')
				exp_dollar(shell, res, cmd, i);
			else
				ft_exp_double_quote(shell, res, cmd, i);
		}
	}
	(*i)++;
	ft_join_quote(res);
}
