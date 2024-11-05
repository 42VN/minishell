/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 08:30:54 by hitran            #+#    #+#             */
/*   Updated: 2024/11/05 13:08:12 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_logic(t_shell *shell, t_ast *ast)
{
	if (ast->token.type == AND)
	{
		if (ast->left)
			execute_ast(shell, ast->left);
		if (!shell->exitcode && ast->right)
			execute_ast(shell, ast->right);
	}
	else if (ast->token.type == OR)
	{
		if (ast->left)
			execute_ast(shell, ast->left);
		if (shell->exitcode && ast->right)
			execute_ast(shell, ast->right);
	}
}

static void	wait_update(t_shell *shell, pid_t pid)
{
	int		status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		update_status(shell, WEXITSTATUS(status));
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
		exit(shell->exitcode);
	}
	pid[1] = init_child(shell);
	if (pid[1] == 0)
	{
		close(pipe_fd[1]);
		redirect_fd(pipe_fd[0], 0);
		execute_ast(shell, ast->right);
		exit(shell->exitcode);
	}
	close (pipe_fd[0]);
	close (pipe_fd[1]);
	wait_update(shell, pid[1]);
}

void	execute_ast(t_shell *shell, t_ast *ast)
{
	// printf("start execute ast\n");
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
	while (wait(NULL) > 0)
		;
}
