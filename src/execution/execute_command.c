/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:06:57 by hitran            #+#    #+#             */
/*   Updated: 2024/09/27 11:55:17 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipe(int *pipe_id)
{
	if (pipe(pipe_id) == -1)
	{
		perror("Error: pipe");
		exit (1);
	}
}

void	redirect_fd(int from_fd, int to_fd)
{
	if (dup2(from_fd, to_fd) == -1)
	{
		perror("Error: fork");
		close(from_fd);
		exit(1);
	}
	close(from_fd);
}

void	get_redirect(t_shell *shell, t_redirect *redirect, int *fd)
{
	int	pipe_fd[2];

	while (redirect)
	{
		if (redirect->type == RD_HEREDOC)
		{
			create_pipe(pipe_fd);
			write(pipe_fd[1], redirect->path, strlen(redirect->path));
			close (pipe_fd[1]);
			redirect_fd(pipe_fd[0], fd[0]);
		}
		else if (redirect->type == RD_IN)
			fd[0] = open(redirect->path, O_RDONLY);
		else if (redirect->type == RD_OUT)
			fd[1] = open(redirect->path, O_CREAT | O_RDWR | O_TRUNC, 0644);
		else if (redirect->type == RD_APPEND)
			fd[1] = open(redirect->path, O_CREAT | O_RDWR | O_APPEND, 0644);
		// if (fd[0] == -1 || fd[1] == -1)
		// 	open_error(shell, redirect->path, fd);
		redirect = redirect->next;
	}
}

void	execute_command(t_shell *shell, t_token token)
{
	char	*command_path;
	pid_t	pid;
	int		fd[2];

	pid = fork();
	// if (pid == -1)
	// 	fork_error(shell);
	// else 
	if (pid == 0)
	{
		get_redirect(shell, token.redirect, fd);
		if (fd[0] > 2)
			redirect_fd(fd[0], STDIN_FILENO);
		if (fd[1] > 2)
			redirect_fd(fd[1], STDOUT_FILENO);
		command_path = find_command_path(shell->envp, token.cmd);
		execve(command_path, token.split_cmd, shell->envp);
		// exec_error(shell, command_path);
	}
}
