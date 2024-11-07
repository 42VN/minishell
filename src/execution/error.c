/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:13:21 by hitran            #+#    #+#             */
/*   Updated: 2024/11/07 10:29:25 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_error(t_shell *shell, char *path, int *fd)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, path, ft_strlen(path));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
	write(STDERR_FILENO, "\n", 1);
	if (shell->ast)
		ast_cleanup(&shell->ast);
	ft_token_free(shell);
	shell_cleanup(shell);
	// if (fd[0] > 2)
		close (fd[0]);
	// if (fd[1] > 2)
		close (fd[1]);
}

void exec_error(t_shell *shell, char **splitted_cmd, char *command_path)
{
	if (splitted_cmd)
		ft_free_triptr(&splitted_cmd);
	if (command_path)
		free (command_path);
	if (shell->ast)
		ast_cleanup(&shell->ast);
	ft_token_free(shell);
	shell_cleanup(shell);
	exit (126);
}
	
void fork_error(t_shell *shell)
{
	shell_cleanup(shell);
	exit (EXIT_FAILURE);
}
