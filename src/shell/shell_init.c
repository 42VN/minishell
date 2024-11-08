/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:27:58 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/07 21:32:42 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	set_shell_level(t_shell *shell, char **envp)
{
	char	*level;
	char	*res;
	int		num;

	level = env_get(envp, "SHLVL", 0);
	num = ft_atoi(level);
	num++;
	res = ft_itoa(num);
	if (!res)
		return (ft_error_ret("shell_init: malloc", shell, ERR_MALLOC, 0));
	env_set(shell, "SHLVL", res);
	free(res);
	return (1);
}

int	shell_init(t_shell *shell, char **envp)
{
	ft_memset(shell, 0, sizeof(t_shell));
	shell->err_type = ERR_NONE;
	shell->envp = env_dup(envp);
	if (!shell->envp)
		return (0);
	if (set_shell_level(shell, shell->envp) == 0)
		return (0);
	shell->cwd = getcwd(NULL, 0);
	if (!shell->cwd)
	{
		perror("minishell: getcwd");
		shell_cleanup(shell);
		return (0);
	}
	shell->old_pwd = ft_strdup(shell->cwd);
	return (1);
}
