/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:06:57 by hitran            #+#    #+#             */
/*   Updated: 2025/02/03 11:42:31 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_heredoc(char *heredoc)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		free(heredoc);
		heredoc = ft_strdup("pipe");
		return (-1);
	}
	ft_putstr_fd(heredoc, pipe_fd[1]);
	close (pipe_fd[1]);
	return (pipe_fd[0]);
}

static int	redirect_io(t_shell *shell, t_redirect *redirect, int *fd)
{
	while (redirect && redirect->path)
	{
		if (check_ambigous_redir(shell, redirect, fd) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (redirect->type == RD_HEREDOC)
			fd[0] = open_heredoc(redirect->path);
		else if (redirect->type == RD_IN)
			fd[0] = open(redirect->path, O_RDONLY);
		else if (redirect->type == RD_OUT)
			fd[1] = open(redirect->path, O_CREAT | O_RDWR | O_TRUNC, 0664);
		else if (redirect->type == RD_APPEND)
			fd[1] = open(redirect->path, O_CREAT | O_RDWR | O_APPEND, 0664);
		if (fd[0] == -1 || fd[1] == -1)
			return (open_error(shell, redirect->path, fd, strerror(errno)));
		if (fd[0] != -1 && fd[0] != -2)
			redirect_fd(fd[0], STDIN_FILENO);
		if (fd[1] != -1 && fd[1] != -2)
			redirect_fd(fd[1], STDOUT_FILENO);
		redirect = redirect->next;
	}
	return (EXIT_SUCCESS);
}

static int	execute_builtin(t_shell *shell, char **token)
{
	if (!ft_strcmp(token[0], "echo"))
		builtin_echo(shell, token);
	else if (!ft_strcmp(token[0], "cd"))
		builtin_cd(shell, token);
	else if (!ft_strcmp(token[0], "pwd"))
		builtin_pwd(shell);
	else if (!ft_strcmp(token[0], "export"))
		builtin_export(shell, token);
	else if (!ft_strcmp(token[0], "unset"))
		builtin_unset(shell, token);
	else if (!ft_strcmp(token[0], "env"))
		builtin_env(shell, token);
	else if (!ft_strcmp(token[0], "exit"))
		builtin_exit(shell, token);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	execute_non_builtin(t_shell *shell, t_token token)
{
	char		*command_path;
	pid_t		pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork2");
		return ;
	}
	if (pid == 0)
	{
		default_signals();
		command_path = find_command_path(shell, token.split_cmd[0]);
		if (!command_path)
		{
			free_all(shell);
			exit (127);
		}
		execve(command_path, token.split_cmd, shell->envp);
		exec_error(shell, command_path, NULL, NULL);
	}
	wait_update(shell, pid);
}

void	execute_command(t_shell *shell, t_token token)
{
	int			fd[2];
	const int	tmp[2] = {dup(STDIN_FILENO), dup(STDOUT_FILENO)};

	fd[0] = -2;
	fd[1] = -2;
	if (redirect_io(shell, token.redirect, fd) == EXIT_FAILURE)
	{
		redirect_fd(tmp[0], STDIN_FILENO);
		redirect_fd(tmp[1], STDOUT_FILENO);
		return ;
	}
	env_underscore(shell, token.split_cmd);
	if (token.cmd && token.split_cmd && token.split_cmd[0])
	{
		if (execute_builtin(shell, token.split_cmd) == EXIT_FAILURE)
			execute_non_builtin(shell, token);
	}
	redirect_fd(tmp[0], STDIN_FILENO);
	redirect_fd(tmp[1], STDOUT_FILENO);
}
