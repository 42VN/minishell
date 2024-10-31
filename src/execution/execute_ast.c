/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 08:30:54 by hitran            #+#    #+#             */
/*   Updated: 2024/10/31 14:34:03 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_logic(t_shell *shell, t_ast *ast)
{
	if (ast->token.type == AND)
	{
		if (ast->left)
			execute_ast(shell, ast->left);
		if (update_status(-1) == 0 && ast->right)
			execute_ast(shell, ast->right);
	}
	else if (ast->token.type == OR)
	{
		if (ast->left)
			execute_ast(shell, ast->left);
		if (update_status(-1) != 0 && ast->right)
			execute_ast(shell, ast->right);
	}
}

static void	wait_and_close(int *pipe_fd, pid_t *pid)
{
	int		status;

	waitpid(pid[1], &status, 0);
	update_status((status >> 8) & 255);
	waitpid(pid[0], NULL, 0);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

static void	execute_pipe(t_shell *shell, t_ast *ast)
{
	int		pipe_fd[2];
	pid_t	pid[2];

	create_pipe(pipe_fd);
	pid[0] = init_child(shell);
	if (pid[0] == 0)
	{
		close(pipe_fd[0]);
		redirect_fd(pipe_fd[1], 1);
		execute_ast(shell, ast->left);
		exit(EXIT_SUCCESS);
	}
	pid[1] = init_child(shell);
	if (pid[1] == 0)
	{
		close(pipe_fd[1]);
		redirect_fd(pipe_fd[0], 0);
		execute_ast(shell, ast->right);
		exit(EXIT_SUCCESS);
	}
}

void	execute_ast(t_shell *shell, t_ast *ast)
{
	if (ast->token.type == AND || ast->token.type == OR)
		execute_logic(shell, ast);
	else if (ast->token.type == PIPE)
		execute_pipe(shell, ast);
	else if (ast->left)
		execute_ast(shell, ast->left);
	else if (ast->right)
		execute_ast(shell, ast->right);
	else if (ast->token.type == CMD)
		execute_command(shell, ast->token);
}
