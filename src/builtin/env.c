/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:49:27 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/21 15:15:08 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(t_shell *shell, char **split_cmd)
{
	if (!shell || !split_cmd || !split_cmd[0])
	{
		ft_putstr_fd("minishell: builtin_env: Invalid parameter(s)\n", 2);
		update_status(shell, 1);
		return ;
	}
	if (!env_get(shell->envp, "PATH", 1))
	{
		ft_putstr_fd("minishell: env: No such file or directory\n", 2);
		update_status(shell, 127);
		return ;
	}
	env_print(shell->envp);
}
