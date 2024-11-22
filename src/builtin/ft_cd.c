/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:02:39 by mito              #+#    #+#             */
/*   Updated: 2024/06/27 17:38:16 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "builtin.h"
#include "utils.h"
#include "minishell.h"
#include "constants.h"

static int	update_path(const char *current_path, t_minishell *minishell)
{
	char	*temp;

	if (
		update_env_cd("OLDPWD", minishell->cwd, minishell->env_list) < 0
		|| update_env_cd("OLDPWD", minishell->cwd, minishell->export_list) < 0
	)
		return (-1);
	temp = ft_strdup(current_path);
	if (temp == NULL)
		return (-1);
	free(minishell->cwd);
	minishell->cwd = temp;
	if (
		update_env_cd("PWD", minishell->cwd, minishell->env_list) < 0
		|| update_env_cd("PWD", minishell->cwd, minishell->export_list) < 0
	)
		return (-1);
	return (0);
}

static int	go_home(t_minishell *minishell)
{
	const char	*home_path = find_env("HOME", minishell->env_list);

	if (home_path == NULL)
	{
		ft_fprintf(STDERR_FILENO, "minishell: cd: %s\n", "HOME not set");
		return (-1);
	}
	if (chdir(home_path) == -1)
	{
		ft_fprintf(\
			2, "minishell: cd: %s: %s\n", home_path, strerror(errno) \
		);
		return (-1);
	}
	if (update_path(home_path, minishell) < 0)
		return (1);
	return (0);
}

static int	go_to_dir(const char *path, t_minishell *minishell)
{
	char	buffer[PATH_MAX];

	if (chdir(path) == -1)
	{
		ft_fprintf(2, "minishell: cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	if (getcwd(buffer, PATH_MAX) == NULL)
	{
		ft_fprintf(\
			STDERR_FILENO, \
			"%s: %s: %s\n", \
			"minishell: cd: error retrieving current directory", \
			"getcwd: cannot access parent directories", \
			strerror(errno) \
		);
		return (0);
	}
	if (update_path(buffer, minishell) < 0)
		return (1);
	return (0);
}

int	ft_cd(t_command *cmd, void *minishell)
{
	if (cmd->argv[1] == NULL)
	{
		if (go_home(minishell) < 0)
			return (1);
		return (0);
	}
	if (cmd->argv[1][0] == '\0')
		return (0);
	if (cmd->argv[2] != NULL)
	{
		ft_fprintf(STDERR_FILENO, "minishell: cd: too many arguments\n");
		return (1);
	}
	return (go_to_dir(cmd->argv[1], minishell));
}
