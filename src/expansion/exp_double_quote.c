/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_double_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:20:20 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/02 17:17:37 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_exp_double_quote(t_shell *shell, char **res, char *cmd, size_t *i)
{
	char	*str;
	char	*joined;
	size_t	start;

	start = *i;
	while (cmd[*i] && cmd[*i] != '\"' && cmd[*i] != '$')
		(*i)++;
	if (!cmd[*i])
		return (ft_free_null(res));
	str = ft_substr(cmd, start, *i - start);
	if (!str)
	{
		ft_error_ret("exp_double_quote: ft_substr: malloc", shell, ERR_MALLOC, 0);
		return (ft_free_null(res));
	}
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

/**
 * No enclosing quote handler
 */
void	exp_double_quote_no_enclosing(t_shell *shell, char **res, char *cmd, size_t *i)
{
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
}
