/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 08:30:54 by hitran            #+#    #+#             */
/*   Updated: 2024/11/08 12:01:04 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to handle logical execution of AND/OR operators in the AST
 * Description:
 * - Executes the left and right branches of the AST based on the operator type
 *  (AND/OR).
 * - For AND, the right branch is executed only if the left branch succeeds
 *   (exit code 0).
 * - For OR, the right branch is executed only if the left branch fails
 *   (non-zero exit code).
 * - Recursively calls execute_ast for both left and right nodes when necessary.
 */
static void	execute_logic(t_shell *shell, t_ast *ast)
{
	if (!ast)
		return ;
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

/**
 * Function to execute child processes in a pipeline
 * Description:
 * - Handles execution of the left or right side of a pipeline based on the 
 *   value of the 'left' flag.
 * - Closes the appropriate pipe ends and redirects the file descriptors using 
 *   redirect_fd.
 * - Recursively calls execute_ast to execute the corresponding AST node.
 * - Frees all shell resources and exits with the exit code after execution.
 */
static void	execute_child(t_shell *shell, t_ast *ast, int *pipe_fd, int left)
{
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

/**
 * Function to initialize a child process by forking
 * Description:
 * - Calls fork() to create a child process.
 * - Returns EXIT_FAILURE if forking fails, otherwise returns EXIT_SUCCESS.
 * - Closes pipe file descriptors if forking fails to prevent resource leakage.
 */
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

/**
 * Function to handle the execution of a pipeline (with two child processes)
 * Description:
 * - Creates a pipe using pipe().
 * - Initializes two child processes using fork().
 * - The first child process executes the left side of the pipe, while the 
 *   second executes the right side.
 * - Calls execute_child for both child processes, passing the appropriate 
 *   pipe and side flags.
 * - Waits for the second child process to finish execution before closing the 
 *   pipe and returning.
 */
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

/**
 * Function to execute the abstract syntax tree (AST) of a command
 * Description:
 * - Executes the appropriate action based on the token type of the AST node.
 * - For logical operators (AND/OR), it calls execute_logic.
 * - For pipes, it calls execute_pipe.
 * - Recursively calls execute_ast for left and right children as needed.
 * - For command nodes (CMD), it calls execute_command to run the command.
 * - Waits for any child processes to complete.
 */
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
	while (wait(NULL) > 0)
		;
}
