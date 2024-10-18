/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:28:33 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/18 15:54:39 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	shell_cleanup(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->envp)
		ft_multi_free_null(&shell->envp);
	if (shell->cwd)
	{
		free(shell->cwd);
		shell->cwd = NULL;
	}
	shell->aborted = 0;
}
