/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:06:57 by hitran            #+#    #+#             */
/*   Updated: 2024/11/15 11:13:18 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to open a pipe for a heredoc
 * Description:
 * - Creates a pipe to simulate the heredoc behavior.
 * - Writes the content of the heredoc string to the pipe.
 * - Closes the write end of the pipe.
 * Returns:
 * - The read end of the pipe, which can be used for input redirection.
 * - If an error occurs while creating the pipe, it frees the heredoc string and
 *   sets it to "pipe" before returning -1.
 */
static int	open_heredoc(char *heredoc)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		free(heredoc);
		heredoc = ft_strdup("pipe");
		return (-1);
	}
	write(pipe_fd[1], heredoc, ft_strlen(heredoc));
	close (pipe_fd[1]);
	return (pipe_fd[0]);
}

/**
 * Function to handle input and output redirection for commands
 * Description:
 * - Iterates over the list of redirects and opens the necessary files or pipes.
 * - Supports:
 * 	 input redirection (RD_IN), 
 * 	 output redirection (RD_OUT),
 * 	 append redirection (RD_APPEND),
 * 	 and heredoc (RD_HEREDOC).
 * - If a file cannot be opened or a heredoc cannot be created, 
 * 	 it calls open_error to report the issue.
 * - Redirects the file descriptors for stdin and stdout as needed.
 * Returns:
 * - EXIT_SUCCESS if all redirections are set up correctly, or 
 * - EXIT_FAILURE if an error occurs.
 */
static int	redirect_io(t_shell *shell, t_redirect *redirect, int *fd)
{
	int	pipe_fd[2];

	while (redirect)
	{
		if (redirect->type == RD_HEREDOC)
			fd[0] = open_heredoc(redirect->path);
		else if (redirect->type == RD_IN)
			fd[0] = open(redirect->path, O_RDONLY);
		else if (redirect->type == RD_OUT)
			fd[1] = open(redirect->path, O_CREAT | O_RDWR | O_TRUNC, 0644);
		else if (redirect->type == RD_APPEND)
			fd[1] = open(redirect->path, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd[0] == -1 || fd[1] == -1)
		{
			open_error(shell, redirect->path, fd);
			return (EXIT_FAILURE);
		}
		redirect = redirect->next;
	}
	if (fd[0] != -2)
		redirect_fd(fd[0], STDIN_FILENO);
	if (fd[1] != -2)
		redirect_fd(fd[1], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

/**
 * Function to execute built-in commands
 * Description:
 * - Checks the command token against a list of known built-in commands:
 * 	 echo, cd, pwd, export, unset, env, exit.
 * - Calls the corresponding built-in function if the command matches.
 * Returns:
 * - EXIT_FAILURE if the command is not recognized as a built-in.
 */
static int	execute_builtin(t_shell *shell, char **token)
{
	if (!token || !token[0])
		return (EXIT_FAILURE);
	if (!ft_strcmp(token[0], "echo"))
		return (builtin_echo(token));
	else if (!ft_strcmp(token[0], "cd"))
		return (builtin_cd(shell, token));
	else if (!ft_strcmp(token[0], "pwd"))
		return (builtin_pwd(shell));
	else if (!ft_strcmp(token[0], "export"))
		return (builtin_export(shell, token));
	else if (!ft_strcmp(token[0], "unset"))
		return (builtin_unset(shell, token));
	else if (!ft_strcmp(token[0], "env"))
		return (builtin_env(shell, token));
	else if (!ft_strcmp(token[0], "exit"))
		return (builtin_exit(shell, token));
	return (EXIT_FAILURE);
}

/**
 * Function to execute non-built-in commands
 * Description:
 * - Forks a child process to execute a non-built-in command.
 * - Searches for the command's path using find_command_path.
 * - If the command is found, it executes the command using execve.
 * - If the command is not found, it frees resources and exits with failure.
 * - Waits for the child process to complete before returning.
 */
void	execute_non_builtin(t_shell *shell, t_token token)
{
	char		*command_path;
	pid_t		pid;
	int			fd[2];
	int			status;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork2");
		return ;
	}
	if (pid == 0)
	{
		set_signals(shell, CHILD); //811
		command_path = find_command_path(shell->envp, token.split_cmd[0]);
		if (!command_path)
		{
			// ft_free_triptr(&token.split_cmd);
			free_all(shell);
			exit (EXIT_FAILURE);
		}
		execve(command_path, token.split_cmd, shell->envp);
		exec_error(shell, token.split_cmd, command_path);
	}
	// print_signaled(shell);
	wait_update(shell, pid);
}

/**
 * Function to execute a command, either built-in or non-built-in
 * Description:
 * - Handles redirection of input and output by calling redirect_io.
 * - Splits the command into tokens using split_command.
 * - If the command is a built-in, it calls execute_builtin.
 * - If the command is non-built-in, it calls execute_non_builtin.
 * - Restores the original stdin and stdout file descriptors after execution.
 * - Frees any allocated memory for the command tokens after execution.
 */
void	execute_command(t_shell *shell, t_token token)
{
	char		*command_path;
	int			fd[2];
	int			status;
	const int	tmp[2] = {dup(STDIN_FILENO), dup(STDOUT_FILENO)};

	fd[0] = -2;
	fd[1] = -2;
	if (redirect_io(shell, token.redirect, fd) == EXIT_FAILURE)
		return ;
	if (execute_builtin(shell, token.split_cmd) == EXIT_FAILURE)
		execute_non_builtin(shell, token);
	redirect_fd(tmp[0], STDIN_FILENO);
	redirect_fd(tmp[1], STDOUT_FILENO);
	// if (token.split_cmd)
	// 	ft_free_triptr(&token.split_cmd);
}
