/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:02:35 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/12 16:20:29 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Function to get the value from the key-pair value from env list
 * 
 * Description:
 * 
 * -	If <include_key> is true and key is found,
 * this function returns full variable string.
 * Otherwise, it will return the value.
 * 
 */
char	*env_get(char **envp, char *key, int include_key)
{
	int		i;
	size_t	len;

	if (!envp || !key)
		return (NULL);
	i = 0;
	len = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strcmp(key, envp[i]) == 0
			&& *(envp[i] + len) == '=')
		{
			if (include_key)
				return (envp[i]);
			else
				return (envp[i] + len + 1);
		}
		++i;
	}
	return (NULL);
}
