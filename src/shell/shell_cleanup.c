/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:28:33 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/06 17:50:30 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_envp(char **envp)
{
	int i;

	if (!envp)
		return;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	shell_cleanup(t_shell *shell)
{
	if (!shell)
		return;

	if (shell->envp)
		free_envp(shell->envp);

	if (shell->cwd)
	{
		free(shell->cwd);
		shell->cwd = NULL;
	}

	shell->exited = 0;
	shell->aborted = 0;
}