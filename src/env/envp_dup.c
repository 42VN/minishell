/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:42:24 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/13 14:25:45 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**envp_dup(char **envp)
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
