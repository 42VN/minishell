/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:16:00 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/15 23:40:34 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Expansion function searching for an env variable
 */
static char	*exp_dollar_get_var(t_shell *shell, char *cmd, size_t *j)
{
	char	*exp_var;
	char	*env_var_val;
	char	*res;
	size_t	start;

	start = *j;
	while (exp_valid_dollar_var(cmd[*j]))
		(*j)++;
	exp_var = ft_substr(cmd, start, *j - start);
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
		return (ft_error_ret("exp_dollar: malloc", shell, ERR_MALLOC, 0));
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
	char *cmd
)
{
	char	*str;
	char	*joined;
	size_t	j;

	j = 0;
	j++;
	if (cmd[j] == '@' || ft_isdigit(cmd[j]))
		(j)++;
	if (exp_is_normal_str(cmd[j]))
		return;
	else if (cmd[j] == '?')
	{
		j++;
		str = ft_itoa(shell->exitcode);
	}
	else if (!exp_valid_dollar_var(cmd[j]))
		str = ft_strdup("$");
	else
		str = exp_dollar_get_var(shell, cmd, &j);
	if (!str)
		return (ft_free_null(res));
	joined = ft_strjoin(*res, str);
	free(*res);
	free(str);
	*res = joined;
}
