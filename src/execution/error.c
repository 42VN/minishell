/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:13:21 by hitran            #+#    #+#             */
/*   Updated: 2024/10/18 10:25:32 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_error(t_shell *shell, char *path, int *fd)
{
	shell_cleanup(shell);
	if (fd[0] > 2)
		close (fd[0]);
	if (fd[1] > 2)
		close (fd[1]);
}

void exec_error(shell, command_path)
{
	shell_cleanup(shell);
	exit (EXIT_FAILURE); //will be updated to errno
}
	
void fork_error(shell)
{
	shell_cleanup(shell);
	exit (EXIT_FAILURE);
}
