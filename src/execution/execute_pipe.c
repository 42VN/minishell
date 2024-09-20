/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 08:31:14 by hitran            #+#    #+#             */
/*   Updated: 2024/09/20 13:15:01 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	left_process(t_shell *shell, t_ast *ast, int *pipe_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		handle_fork_error(pipe_fd);
	else if (pid == 0)
	{
		close(pipe_fd[0]);
		redirect_fd(pipe_fd[1], 1);
		execute_ast(shell, ast->left);
	}
	close(pipe_fd[1]);
}

static void	right_process(t_shell *shell, t_ast *ast, int *pipe_fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		handle_fork_error(pipe_fd);
	else if (pid == 0)
	{
		close(pipe_fd[1]);
		redirect_fd(pipe_fd[0], 0);
		execute_ast(shell, ast->right);
	}
	close(pipe_fd[0]);
	waitpid(pid, &status, 0);
	update_status((status >> 8) & 255);
}

void	execute_pipe(t_shell *shell, t_ast *ast)
{
	int		pipe_fd[2];
	pid_t	pid[2];

	create_pipe(pipe_fd);
	left_process(shell, ast, pipe_fd);
	right_process(shell, ast, pipe_fd);
	while (wait(NULL) > 0)
		;
}
