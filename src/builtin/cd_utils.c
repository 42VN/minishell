/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:42:06 by hitran            #+#    #+#             */
/*   Updated: 2024/12/18 15:39:06 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_error(t_shell *shell, char *s, int error_num)
{
	ft_putstr_fd(s, STDERR_FILENO);
	update_status(shell, error_num);
	return (EXIT_FAILURE);
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
