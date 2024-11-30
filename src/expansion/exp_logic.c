/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_logic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:10:41 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/30 02:30:11 by ktieu            ###   ########.fr       */
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

static char*	exp_pre_process(t_shell *shell, char **res, char *cmd)
{
	size_t	k;
	char	*clone;

	k = 0;
	// clone = ft_strdup("");
	// while (cmd[k])
	// {
	// 	if (cmd[k] == '\"')
	// 	{
	// 		printf("Quote Before: [%s]\n", &cmd[k]);
	// 		exp_double_quote(shell, &clone, cmd, &k);
	// 		// printf("Quote Before: [%s]\n", clone);
	// 	}
	// 	else
	// 		k++;
	// }
	clone = ft_token_parse(&cmd, shell, 1);
	if (!*clone)
	{
		free(clone);
		clone = ft_strdup(cmd);
	}
	else
		exp_remove_quotes(&clone, 0);
	return (clone);
}

static int	exp_process(t_shell *shell, char **res, char *cmd)
{
	size_t	k;
	char	*clone;

	k = 0;
	// clone = exp_pre_process(shell, res, cmd);
	clone = cmd;
	k = 0;
	if (*clone == '~')
		exp_tiddle_front(shell, res, clone, &k);
	while (clone[k])
	{
		if (clone[k] == '$')
			exp_dollar(shell, res, clone, &k);
		else if (clone[k] == '~')
			exp_tiddle(res, clone, &k);
		else if (clone[k] == '\'')
			exp_single_quote(res, clone, &k);
		else if (clone[k] == '\"')
			exp_double_quote(shell, res, clone, &k);
		else
			exp_normal(res, clone, &k);
	}
	// if (clone)
	// 	free(clone);
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
