/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:11:40 by hitran            #+#    #+#             */
/*   Updated: 2024/12/18 15:00:00 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**find_envp_path(char **envp)
{
	char	**cwd;

	while (*envp && !ft_strnstr(*envp, "PATH=", 5))
		envp++;
	if (!*envp ||!ft_strcmp(*envp, "PATH="))
	{
		cwd = (char **)ft_calloc(2, sizeof(char *));
		if (!cwd)
			return (NULL);
		cwd[0] = getcwd(NULL, 0);
		if (!cwd[0])
		{
			free_array(cwd);
			return (NULL);
		}
		return (cwd);
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

	if (!command || !command[0]
		|| !ft_strcmp(command, ".") || !ft_strcmp(command, ".."))
		return (check_error(command));
	else if (ft_strchr(command, '/'))
	{
		if (stat(command, &sb) == 0 && S_ISDIR(sb.st_mode))
			exec_error (shell, NULL, command, "Is a directory");
		else if (stat(command, &sb) == 0 && access(command, X_OK) != 0)
			exec_error (shell, NULL, command, "Permission denied");
		else if (access(command, F_OK) != 0)
			return (check_error(command));
	}
	return (EXIT_SUCCESS);
}

char	*find_command_path(t_shell *shell, char *command)
{
	char		**envp_paths;
	char		*command_path;

	if (check_command(shell, command) == EXIT_FAILURE)
		return (NULL);
	if (ft_strchr(command, '/') && access(command, F_OK) == 0)
		return (ft_strdup(command));
	envp_paths = find_envp_path(shell->envp);
	if (!envp_paths)
		return (NULL);
	command_path = get_command_path(envp_paths, command);
	ft_free_triptr(&envp_paths);
	if (!command_path)
		ft_printf_fd(STDERR_FILENO, "%s: command not found\n", command);
	else if (access(command_path, X_OK) != 0)
		exec_error (shell, NULL, command, "Permission denied");
	return (command_path);
}
