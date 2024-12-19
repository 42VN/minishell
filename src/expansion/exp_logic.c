/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_logic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:10:41 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/19 13:48:09 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exp_process(t_shell *shell, char **res, char *cmd)
{
	size_t	k;
	char	*clone;

	k = 0;
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
	return (1);
}

int	exp_logic_str_helper(char **res)
{
	size_t	len;
	char	**split_cmd;

	len = 0;
	split_cmd = ft_split_quote_wc(*res);
	if (!split_cmd)
		return (0);
	free(*res);
	while (split_cmd[len])
		(len)++;
	exp_split_cmd_remove_quotes(split_cmd, len);
	*res = exp_split_cmd_join(split_cmd);
	if (!res)
		return (0);
	ft_multi_free_null(&split_cmd);
	return (1);
}

int	exp_logic_str(t_shell *shell, char **str)
{
	char	*res;

	res = ft_strdup("");
	if (!res)
		return (ft_error_ret("expansion: exp_logic_str: ft_strdup",
				shell, ERR_MALLOC, 0));
	exp_process(shell, &res, *str);
	if (!res)
		return (ft_error_ret("expansion: exp_logic_str: malloc",
				shell, ERR_MALLOC, 0));
	if (!exp_logic_str_helper(&res))
		return (ft_error_ret("expansion: exp_logic_str: malloc",
				shell, ERR_MALLOC, 0));
	ft_free_null(str);
	*str = res;
	return (1);
}

int	exp_logic_split_str(t_shell *shell, char **str, char ***split_cmd)
{
	char	*res;

	if (!*split_cmd)
		return (0);
	res = ft_strdup("");
	if (!res)
		return (ft_error_ret("expansion: exp_logic_split_str: ft_strdup",
				shell, ERR_MALLOC, 0));
	exp_process(shell, &res, *str);
	if (!res)
		return (ft_error_ret("expansion: exp_logic_split_str: malloc",
				shell, ERR_MALLOC, 0));
	ft_free_null(str);
	exp_split_cmd_push_back(shell, split_cmd, res);
	free(res);
	return (1);
}
