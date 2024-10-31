/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:27:58 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/31 14:51:21 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	shell_init(t_shell *shell, char **envp)
{
	ft_memset(shell, 0, sizeof(t_shell));
	shell->err_type = ERR_NONE;
	shell->envp = env_dup(envp);
	if (!shell->envp)
		return (0);
	shell->cwd = getcwd(NULL, 0);
	if (!shell->cwd)
	{
		perror("minishell: getcwd");
		shell_cleanup(shell);
		return (0);
	}
	shell->old_pwd = ft_strdup(shell->cwd);
	return (1);
}
