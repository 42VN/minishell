/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:49:27 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/31 13:54:30 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
 
int	builtin_env(t_shell *shell, char **split_cmd)
{
	if (!shell || !split_cmd || !split_cmd[0])
	{
		ft_putstr_fd("minishell: builtin_env: Invalid parameter(s)\n", 2);
		return (1);
	}
	if (!env_get(shell->envp, "PATH", 1))
	{
		ft_putstr_fd("minishell: env: No such file or directory\n", 2);
		return (127);
	}
	env_print(shell->envp);
	return (0);
}
