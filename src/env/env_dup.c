/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 13:54:55 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/18 16:07:57 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_dup(char **envp)
{
	char	**res;
	int		i;

	i = 0;
	while (envp && envp[i])
		++i;
	res = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (envp && envp[i])
	{
		res[i] = ft_strdup(envp[i]);
		if (!res[i])
		{
			ft_multi_free_null(&res);
			return (NULL);
		}
		++i;
	}
	return (res);
}

char	**env_dup_sorted(char **envp)
{
	char	**sorted_envp;

	sorted_envp = env_dup(envp);
	if (!sorted_envp)
		return (NULL);
	env_sort(sorted_envp);
	return (sorted_envp);
}
