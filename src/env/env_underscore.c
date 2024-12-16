/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_underscore.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:04:57 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/16 09:54:10 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_underscore(t_shell *shell, char **split_cmd)
{
	int		i;
	char	*last_cmd ;

	i = 0;
	if (split_cmd)
	{
		while (split_cmd && split_cmd[i])
			++i;
		if (i > 0 && shell->tokens->has_pipe == 0)
		{
			last_cmd = split_cmd[i - 1];
			env_set(shell, "_", last_cmd);
		}
	}
	return (1);
}

int	env_clone_underscore(t_shell *shell)
{
	char	*underscore_val;

	underscore_val = env_get(shell->envp, "_", 0);
	if (underscore_val && *underscore_val)
	{
		shell->tokens->env_last_cmd = ft_strdup(underscore_val);
		if (!shell->tokens->env_last_cmd)
			return (ft_error_ret("env_clone_underscore: ft_strdup",
					shell, ERR_MALLOC, 0));
	}
	return (1);
}
