/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:42:06 by hitran            #+#    #+#             */
/*   Updated: 2024/10/31 14:53:02 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_error(char *s, int error_num)
{
	write(STDERR_FILENO, s, ft_strlen(s));
	update_status(error_num);
	return (EXIT_FAILURE);
}

int	update_pwd(t_shell *shell)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (builtin_error("minishell: getcwd failed\n", 1));
	free(shell->old_pwd);
	shell->old_pwd = shell->cwd;
	shell->cwd = ft_strdup(new_pwd);
	free (new_pwd);
	if (!shell->cwd)
		return (builtin_error("minishell: strdup failed\n", 1));
	env_set(shell, "OLDPWD", shell->old_pwd);
	env_set(shell, "PWD", shell->cwd);
	return (EXIT_SUCCESS);
}
