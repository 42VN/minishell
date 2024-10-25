/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:02:43 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/25 23:00:06 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_shift(t_shell *shell, int i)
{
	while (shell->envp[i + 1])
	{
		shell->envp[i] = shell->envp[i + 1];
		i++;
	}
	shell->envp[i] = NULL;
}

void	env_unset(t_shell *shell, char *key)
{
	int		i;
	size_t	key_len;

	if (!key || !*key || !shell || !shell->envp)
		return ;
	i = 0;
	key_len = ft_strlen(key);
	while (shell->envp[i])
	{
		if (strncmp(shell->envp[i], key, key_len) == 0)
		{
			if (*(shell->envp[i] + key_len) == '='
				|| *(shell->envp[i] + key_len) == '\0')
			{
				free(shell->envp[i]);
				ft_shift(shell, i);
				return ;
			}
		}
		++i;
	}
}
