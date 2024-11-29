/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_logic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:10:41 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/29 17:41:03 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Recusive function remove quotes
 */
int exp_remove_quotes(char **res, int i)
{
	char	quote;
	int		last_quote;
	
	quote = '\0';
	last_quote = -1;
	if (!res || !(*res))
		return (0);
	while ((*res)[i])
	{
		if ((*res)[i] == '\'' || (*res)[i] == '\"')
		{
			quote = (*res)[i];
			last_quote = exp_strip_quotes(*res, quote, i);
			if (last_quote >= i && (*res)[last_quote] != '\0')
			{
				exp_remove_quotes(res, last_quote);
			}
			return (1);
		}
		++i;
	}
	return (1);
}

static int	exp_process(t_shell *shell, char **res, char *cmd)
{
	size_t	k;

	k = 0;
	if (*cmd == '~')
		exp_tiddle_front(shell, res, cmd, &k);
	while (cmd[k])
	{
		if (cmd[k] == '$')
			exp_dollar(shell, res, cmd, &k);
		else if (cmd[k] == '~')
			exp_tiddle(res, cmd, &k);
		else if (cmd[k] == '\'')
			exp_single_quote(res, cmd, &k);
		else if (cmd[k] == '\"')
			exp_double_quote(shell, res, cmd, &k);
		else
			exp_normal(res, cmd, &k);
	}
	return (1);
}

int	exp_logic(t_shell *shell, char **str)
{
	char	*res;

	res = ft_strdup("");
	if (!res)
		return (ft_error_ret("expansion: exp_logic: malloc", shell, ERR_MALLOC, 0));
	exp_process(shell, &res, *str);
	if (!res)
		return (ft_error_ret("expansion: exp_logic: malloc", shell, ERR_MALLOC, 0));
	exp_remove_quotes(&res, 0);
	ft_free_null(str);
	*str = res;
	return (1);
}
