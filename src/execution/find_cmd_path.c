/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:11:40 by hitran            #+#    #+#             */
/*   Updated: 2024/11/07 09:39:51 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**find_envp_path(char **envp, char *command)
{
	while (*envp && !ft_strnstr(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
	{
		write(2, command, ft_strlen(command));
		write(2, ": No such file or directory\n", 26);
		// exit (EXIT_FAILURE);
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
		if (access(command_path, F_OK) == 0)
			return (command_path);
		free(command_path);
	}
	return (NULL);
}

char	*find_command_path(char **envp, char *command)
{
	char	**envp_paths;
	char	*command_path;

	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK) == 0)
			return (ft_strdup(command));
		else
		{
			write(2, command, ft_strlen(command));
			write(2, ": No such file or directory\n", 26);
			return (NULL);
		}
	}
	envp_paths = find_envp_path(envp, command);
	if (!envp_paths)
		return (NULL);
	command_path = get_command_path(envp_paths, command);
	ft_free_triptr(&envp_paths);
	if (!command_path)
	{
		write(2, command, ft_strlen(command));
		write(2, ": Command not found\n", 20);
		// exit (EXIT_FAILURE);
	}
	return (command_path);
}
