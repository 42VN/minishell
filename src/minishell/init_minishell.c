/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:36:12 by mito              #+#    #+#             */
/*   Updated: 2024/06/26 14:11:50 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "minishell.h"
#include "utils.h"

static int	init_cwd(t_minishell *minishell)
{
	minishell->cwd = (char *)malloc(PATH_MAX * sizeof(char));
	if (minishell->cwd == NULL)
		return (-1);
	if (getcwd(minishell->cwd, PATH_MAX) == NULL)
	{
		free(minishell->cwd);
		minishell->cwd = NULL;
		return (-1);
	}
	return (0);
}

static int	init_env_list(t_minishell *minishell, char **envp)
{
	char	*env_var;
	char	*pwd;

	minishell->env_list = ft_list(0);
	if (minishell->env_list == NULL)
		return (-1);
	while (envp != NULL && *envp != NULL)
	{
		env_var = ft_strdup(*envp);
		if (env_var == NULL)
			return (-1);
		if (ft_list_push(minishell->env_list, env_var) < 0)
			return (free(env_var), -1);
		envp++;
	}
	if (find_env("PWD", minishell->env_list) == NULL)
	{
		pwd = ft_join_strings(2, "PWD=", minishell->cwd);
		if (pwd == NULL || ft_list_push(minishell->env_list, pwd) < 0)
			return (free(pwd), -1);
	}
	if (update_shlvl(minishell->env_list) < 0)
		return (-1);
	return (0);
}

static int	init_export_list(t_minishell *minishell)
{
	minishell->export_list = clone_env_list(minishell->env_list);
	if (minishell->export_list == NULL)
		return (-1);
	return (0);
}

int	init_minishell(t_minishell *minishell, char **envp)
{
	minishell->executor = NULL;
	minishell->stdin = dup(STDIN_FILENO);
	minishell->stdout = dup(STDOUT_FILENO);
	if (
		minishell->stdin < 0
		|| minishell->stdout < 0
		|| init_cwd(minishell) < 0
		|| init_env_list(minishell, envp) < 0
		|| init_export_list(minishell) < 0
	)
	{
		delete_minishell(minishell);
		return (-1);
	}
	set_exit_status(0, minishell);
	minishell->should_exit_program = false;
	return (0);
}
