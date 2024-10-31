/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:08:40 by hitran            #+#    #+#             */
/*   Updated: 2024/10/31 14:22:46 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_shell *shell, char **token)
{
	if (!token || !token[0])
		return (0);
	if (!ft_strcmp(token[0], "echo"))	//done
		return (builtin_echo(token));
	else if (!ft_strcmp(token[0], "cd"))
		return (builtin_cd(shell, token));
	else if (!ft_strcmp(token[0], "pwd"))	//done
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
