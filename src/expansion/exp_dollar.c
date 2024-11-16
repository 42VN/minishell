/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:16:00 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/16 00:59:36 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Expansion function searching for an env variable
 */
static char	*exp_dollar_get_var(t_shell *shell, char *cmd, size_t *i)
{
	char	*exp_var;
	char	*env_var_val;
	char	*res;
	size_t	start;

	start = *i;
	while (exp_valid_dollar_var(cmd[*i]))
		(*i)++;
	exp_var = ft_substr(cmd, start, *i - start);
	if (!exp_var)
	{
		return (NULL);
	}
	env_var_val = env_get(shell->envp, exp_var, 0);
	free(exp_var);
	if (!env_var_val)
		res = ft_strdup("");
	else
		res = ft_strdup(env_var_val);
	if (!res)
		return (0);
	return (res);
}

static inline int	exp_is_normal_str(char c)
{
	if (c == '\'' || c == '\"' || c == '@' || ft_isdigit(c))
		return (1);
	return (0);
}

void exp_dollar(
	t_shell *shell,
	char **res,
	char *cmd,
	size_t *i
)
{
	char	*str;
	char	*joined;

	(*i)++;
	if (cmd[*i] == '@' || ft_isdigit(cmd[*i]))
		(*i)++;
	if (exp_is_normal_str(cmd[*i]))
		return;
	else if (cmd[*i] == '?')
	{
		(*i)++;
		str = ft_itoa(shell->exitcode);
	}
	else if (!exp_valid_dollar_var(cmd[*i]))
		str = ft_strdup("$");
	else
		str = exp_dollar_get_var(shell, cmd, i);
	if (!str)
		return (ft_free_null(res));
	joined = ft_strjoin(*res, str);
	free(*res);
	free(str);
	*res = joined;
}
