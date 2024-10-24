/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:02:43 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/18 16:08:29 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void env_unset(t_shell *shell, char *key)
{
	int		i;
	size_t	key_len;

	if (!key || !*key)
		return ;
	i = 0;
	key_len = ft_strlen(key);
	while (shell->envp[i])
	{
		if (ft_strncmp(key, shell->envp[i], key_len) == 0)
		{
			if (*(shell->envp[i] + key_len) == '='
				|| *(shell->envp[i] + key_len) == '\0')
			{
				shell->envp[i] = '\0';
				return ;
			}
		}
		++i;
	}
}
