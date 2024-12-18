/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:42:06 by hitran            #+#    #+#             */
/*   Updated: 2024/12/18 17:17:28 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_error(t_shell *shell, char *s, int error_num)
{
	ft_putstr_fd(s, STDERR_FILENO);
	update_status(shell, error_num);
	return (EXIT_FAILURE);
}

int	inaccessible_parent_dir(t_shell *shell, char *path)
{
	char	*new_pwd;
	char	*temp;

	ft_printf_fd(STDERR_FILENO, "minishell: cd: error retrieving current "
		"directory: getcwd: cannot access parent directories: ");
	perror("");
	temp = ft_strjoin("/", path);
	if (!temp)
		return (EXIT_FAILURE);
	new_pwd = ft_strjoin(shell->cwd, temp);
	free (temp);
	if (!new_pwd)
		return (EXIT_FAILURE);
	free(shell->old_pwd);
	shell->old_pwd = ft_strdup(shell->cwd);
	free(shell->cwd);
	shell->cwd = ft_strdup(new_pwd);
	free (new_pwd);
	if (!shell->old_pwd || !shell->cwd)
		return (builtin_error(shell, "minishell: strdup failed\n", 1));
	env_set(shell, "OLDPWD", shell->old_pwd);
	env_set(shell, "PWD", shell->cwd);
	update_status(shell, 0);
	return (EXIT_SUCCESS);
}

int	update_pwd(t_shell *shell)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		new_pwd = ft_strjoin(shell->cwd, "/..");
	free(shell->old_pwd);
	shell->old_pwd = ft_strdup(shell->cwd);
	free(shell->cwd);
	shell->cwd = ft_strdup(new_pwd);
	free (new_pwd);
	if (!shell->old_pwd || !shell->cwd)
		return (builtin_error(shell, "minishell: strdup failed\n", 1));
	env_set(shell, "OLDPWD", shell->old_pwd);
	env_set(shell, "PWD", shell->cwd);
	update_status(shell, 0);
	return (EXIT_SUCCESS);
}
