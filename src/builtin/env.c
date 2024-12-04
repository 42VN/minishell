/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:49:27 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/04 14:13:23 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	builtin_env_check(t_shell *shell, char **split_cmd, size_t len)
{
	char	*arg;

	if (len > 1)
	{
		arg = split_cmd[1];
		if (!*arg)
		{
			ft_printf_fd(2, "env: ‘’: No such file or directory\n");
			update_status(shell, 127);
		}
		else if (*arg == '-')
		{
			ft_printf_fd(2, "env: unrecognized option '%s'\n", arg);
			update_status(shell, 125);
		}
		else
		{
			ft_printf_fd(2, "env: ‘%s’: Permission denied\n", arg);
			update_status(shell, 126);
		}
		return (0);
	}
	return (1);
}

void	builtin_env(t_shell *shell, char **split_cmd)
{
	size_t	len;

	len = 0;
	while (split_cmd[len])
		len++;
	if (!shell || !split_cmd || !split_cmd[0])
	{
		ft_putstr_fd("minishell: builtin_env: Invalid parameter(s)\n", 2);
		update_status(shell, 1);
		return ;
	}
	if (!builtin_env_check(shell, split_cmd, len))
		return ;
	if (!env_get(shell->envp, "PATH", 1))
	{
		ft_putstr_fd("minishell: env: No such file or directory\n", 2);
		update_status(shell, 127);
		return ;
	}
	env_print(shell->envp);
}
