/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:13:21 by hitran            #+#    #+#             */
/*   Updated: 2024/11/19 22:09:54 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function that frees all allocated resources in the shell structure
 * Description:
 * - Frees the abstract syntax tree (AST) if it exists.
 * - Calls ft_token_free to free token-related data.
 * - Calls shell_cleanup to release other resources associated with the shell.
 */
void	free_all(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->ast)
		ast_cleanup(&shell->ast);
	ft_token_free(shell);
	shell_cleanup(shell);
}

/**
 * Function to handle file opening errors
 * Description:
 * - Prints an error message to stderr.
 * - Frees all shell resources by calling free_all.
 * - Closes the file descriptors specified in fd array.
 */
void	open_error(t_shell *shell, char *path, int *fd)
{
	ft_printf_fd(2, "minishell: %s: %s\n", path, strerror(errno));
	free_all(shell);
	close (fd[0]);
	close (fd[1]);
}

void	exec_error(t_shell *shell, char *command_path)
{
	if (command_path)
		free (command_path);
	free_all(shell);
	exit (126);
}
