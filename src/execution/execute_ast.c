/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 08:30:54 by hitran            #+#    #+#             */
/*   Updated: 2024/12/17 13:18:32 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_logic(t_shell *shell, t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->left)
		execute_ast(shell, ast->left);
	if (ast->token.type == AND && !shell->exitcode && ast->right)
		execute_ast(shell, ast->right);
	else if (ast->token.type == OR && shell->exitcode && ast->right)
		execute_ast(shell, ast->right);
}

static void	execute_child(t_shell *shell, t_ast *ast, int *pipe_fd, int left)
{
	start_signal(shell, CHILD);
	if (left)
	{
		close(pipe_fd[0]);
		redirect_fd(pipe_fd[1], 1);
		execute_ast(shell, ast->left);
	}
	else
	{
		close(pipe_fd[1]);
		redirect_fd(pipe_fd[0], 0);
		execute_ast(shell, ast->right);
	}
	free_all(shell);
	exit(shell->exitcode);
}

static int	init_child(int *pipe_fd, pid_t	*pid)
{
	*pid = fork();
	if (*pid == -1)
	{
		perror("minishell: fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	execute_pipe(t_shell *shell, t_ast *ast)
{
	int		pipe_fd[2];
	pid_t	pid[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return ;
	}
	if (init_child(pipe_fd, &pid[0]) == EXIT_FAILURE)
		return ;
	if (pid[0] == 0)
		execute_child(shell, ast, pipe_fd, 1);
	if (init_child(pipe_fd, &pid[1]) == EXIT_FAILURE)
		return ;
	if (pid[1] == 0)
		execute_child(shell, ast, pipe_fd, 0);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	wait_update(shell, pid[1]);
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
	{
		if (ast->token.cmd && (!ft_strcmp(ast->token.cmd, "./minishell") 
			|| !ft_strcmp(ast->token.cmd, "./minishell_bonus")))
			minishell(shell);
		else
			execute_command(shell, ast->token);
	}
	while (wait(NULL) > 0)
		;
}
