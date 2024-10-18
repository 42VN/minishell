/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:48:57 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/18 16:08:25 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	env_arg_count(char **envp)
{
	size_t	len;

	len = 0;
	if (!envp)
		return (0);
	while (envp[len])
		++len;
	return (len);
}

void	env_sort(char **envp)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*temp;

	i = 0;
	len = 0;
	len = env_arg_count(envp);
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(envp[i], envp[j]) > 0)
			{
				temp = envp[i];
				envp[i] = envp[j];
				envp[j] = temp;
			}
			++j;
		}
		++i;
	}
}
