/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:13:21 by hitran            #+#    #+#             */
/*   Updated: 2024/11/22 23:22:47 by hitran           ###   ########.fr       */
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
int	open_error(t_shell *shell, char *path, int *fd, char *message)
{
	ft_printf_fd(2, "minishell: %s: %s\n", path, message);
	if (fd[0] != -1 && fd[0] != -2)
		close (fd[0]);
	if (fd[1] != -1 && fd[1] != -2)
		close (fd[1]);
	update_status(shell, 1);
	return (EXIT_FAILURE);
}

void	exec_error(t_shell *shell, char *command_path)
{
	if (command_path)
		free (command_path);
	free_all(shell);
	exit (update_status(shell, 126));
}
