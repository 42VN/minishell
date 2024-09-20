/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:06:57 by hitran            #+#    #+#             */
/*   Updated: 2024/09/20 12:49:17 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	create_pipe(int *pipe_id)
{
	if (pipe(pipe_id) == -1)
	{
		perror("Failed to create a pipe\n"); // print message
		exit (1);
	}
}

void	redirect_fd(int from_fd, int to_fd)
{
	if (dup2(from_fd, to_fd) == -1)
	{
		perror("Failed to dup2"); // print message
		close(from_fd);
		exit(1);
	}
	close(from_fd);
}

void	redirect_io(t_shell *shell, t_redirect *redirect)
{
	int		pipe_fd[2];
	int		fd[2];

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
		if (fd[0] == -1 || fd[1] == -1)
			open_error(redirect->path, fd); // handle error
		redirect = redirect->next;
	}
	redirect_fd(fd[0], 0);
	redirect_fd(fd[1], 1);
}

void	excecute_command(t_shell *shell, t_token token)
{
	char	*command_path;

	redirect_io(shell, token.redirect);
	command_path = find_command_path(shell->envp, token.split_cmd);
	if (!command_path)
		path_error(); //handle error
	execve(command_path, token.splitted_cmd, shell->envp);
	exec_error(command_path, token.splitted_cmd);
}
