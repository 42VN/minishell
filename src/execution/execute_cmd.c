/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:06:57 by hitran            #+#    #+#             */
/*   Updated: 2024/10/30 21:24:29 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_heredoc(char *heredoc)
{
	int	pipe_fd[2];

	create_pipe(pipe_fd);
	write(pipe_fd[1], heredoc, strlen(heredoc));
	close (pipe_fd[1]);
	return (pipe_fd[0]);
}

static void	redirect_io(t_shell *shell, t_redirect *redirect, int *fd)
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
			open_error(shell, redirect->path, fd);
		redirect = redirect->next;
	}
	if (fd[0] != -2)
		redirect_fd(fd[0], STDIN_FILENO);
	if (fd[1] != -2)
		redirect_fd(fd[1], STDOUT_FILENO);
}

void	execute_command(t_shell *shell, t_token token)
{
	char	*command_path;
	pid_t	pid;
	int		fd[2];
	// char 	**split_cmd;

	fd[0] = -2;
	fd[1] = -2;
	pid = init_child(shell);
	if (pid == 0)
	{
		redirect_io(shell, token.redirect, fd);
		token.split_cmd = split_command(token.cmd);
		if(!execute_builtin(shell, token.split_cmd))
		{
			command_path = find_command_path(shell->envp, token.split_cmd[0]);
			execve(command_path, token.split_cmd, shell->envp);
			exec_error(shell, command_path);
		}
		exit (EXIT_SUCCESS);
	}
}
