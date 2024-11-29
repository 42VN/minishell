/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:11:40 by hitran            #+#    #+#             */
/*   Updated: 2024/11/29 13:34:32 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**find_envp_path(char **envp, char *command)
{
	while (*envp && !ft_strnstr(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
	{
		ft_printf_fd(STDERR_FILENO, "%s: No such file or directory\n", command);
		return (NULL);
	}
	return (ft_split(*envp + 5, ':'));
}

static char	*join_command_path(char *envp_path, char *command)
{
	char	*command_dir;
	char	*command_path;

	command_dir = ft_strjoin(envp_path, "/");
	if (!command_dir)
		return (NULL);
	command_path = ft_strjoin(command_dir, command);
	free(command_dir);
	return (command_path);
}

static char	*get_command_path(char **envp_paths, char *command)
{
	char	*command_path;

	while (*envp_paths)
	{
		command_path = join_command_path(*(envp_paths++), command);
		if (!command_path)
			return (NULL);
		if (access(command_path, F_OK) == 0 || access(command_path, X_OK) == 0)
			return (command_path);
		free(command_path);
	}
	return (NULL);
}

static int	check_command(t_shell *shell, char *command)
{
	struct stat	sb;

	if (!command || !command[0] || !ft_strcmp(command, "."))
	{
		if (!command || !command[0])
			ft_printf_fd(STDERR_FILENO, "Command '%s' not found\n", command);
		else if (!ft_strcmp(command, "."))
			ft_printf_fd(STDERR_FILENO, "minishell: .: filename argument requi"
				"red\n.: usage: . filename [arguments]\n");
		return (EXIT_FAILURE);
	}
	else if (ft_strchr(command, '/'))
	{
		if (stat(command, &sb) == 0 && S_ISDIR(sb.st_mode))
		{
			ft_printf_fd(STDERR_FILENO, "%s: Is a directory\n", command);
			exec_error (shell, NULL);
		}
		else if (stat(command, &sb) == 0 && access(command, X_OK) != 0)
		{
			ft_printf_fd(STDERR_FILENO, "%s: Permission denied\n", command);
			exec_error (shell, NULL);
		}
	}
	return (EXIT_SUCCESS);
}

char	*find_command_path(t_shell *shell, char *command)
{
	char		**envp_paths;
	char		*command_path;

	if (check_command(shell, command) == EXIT_FAILURE)
		return (NULL);
	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK) == 0)
			return (ft_strdup(command));
		ft_printf_fd(STDERR_FILENO, "%s: No such file or directory\n", command);
		return (NULL);
	}
	envp_paths = find_envp_path(shell->envp, command);
	if (!envp_paths)
		return (NULL);
	command_path = get_command_path(envp_paths, command);
	ft_free_triptr(&envp_paths);
	if (!command_path)
		ft_printf_fd(STDERR_FILENO, "%s: command not found\n", command);
	return (command_path);
}
