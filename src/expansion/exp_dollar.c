/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:16:00 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/05 14:57:18 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*exp_handle_dollar_var(t_shell *shell, char *cmd, size_t *j)
{
	
}

void exp_dollar(
	t_shell *shell,
	char **res,
	char *cmd,
	size_t *j)
{
	char	*str;
	char	*joined;
	
	(*j)++;
	if (cmd[*j] == '@' || ft_isdigit(cmd[*j]))
		(j)++;
	if (cmd[*j] == '\'' || cmd[*j] == '\"' || cmd[*j] == '@' || ft_isdigit(cmd[*j]))
		return;
	else if (cmd[*j] == '?')
	{
		(*j)++;
		str = ft_itoa(shell->exitcode);
	}
	else if (!exp_valid_dollar_var(cmd[*j]))
		str = ft_strdup("$");
	else
		str = exp_handle_dollar_var(shell, cmd, j);
	if (!str)
		return (ft_free_null(res));
	joined = ft_strjoin(*res, str);
	ft_free_null(res);
	ft_free_null(str);
	*res = joined;
}
