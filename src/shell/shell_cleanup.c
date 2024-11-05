/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:28:33 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/05 13:27:24 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	shell_cleanup(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->envp)
		ft_multi_free_null(&shell->envp);
	if (shell->ast)
		ast_cleanup(shell->ast);
	if (shell->cwd)
	{
		free(shell->cwd);
		shell->cwd = NULL;
	}
	if (shell->old_pwd)
	{
		free(shell->old_pwd);
		shell->old_pwd = NULL;
	}
	shell->aborted = 0;
}
