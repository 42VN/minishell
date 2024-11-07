/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:06:57 by hitran            #+#    #+#             */
/*   Updated: 2024/11/07 21:21:27 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_heredoc(char *heredoc)
{
	int	pipe_fd[2];

	create_pipe(pipe_fd);
	write(pipe_fd[1], heredoc, ft_strlen(heredoc));
	close (pipe_fd[1]);
	return (pipe_fd[0]);
}

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

void	execute_non_builtin(t_shell *shell, t_token token)
{
	char		*command_path;
	pid_t		pid;
	int			fd[2];
	int			status;

	pid = init_child(shell);
	if (pid == 0)
	{
		command_path = find_command_path(shell->envp, token.split_cmd[0]);
		if (!command_path)
		{
			ft_free_triptr(&token.split_cmd);
			free_all(shell);
			exit (EXIT_FAILURE);
		}
		execve(command_path, token.split_cmd, shell->envp);
		exec_error(shell, token.split_cmd, command_path);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		update_status(shell, WEXITSTATUS(status));
}

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
	token.split_cmd = split_command(token.cmd);
	if (!token.split_cmd)
		return ;
	if (execute_builtin(shell, token.split_cmd) == EXIT_FAILURE)
		execute_non_builtin(shell, token);
	redirect_fd(tmp[0], STDIN_FILENO);
	redirect_fd(tmp[1], STDOUT_FILENO);
	if (token.split_cmd)
		ft_free_triptr(&token.split_cmd);
}
