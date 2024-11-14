/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:02:40 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/14 17:23:45 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Functin to get the index of the key (var) from env list
 */
static int	env_get_index(char **envp, char *key)
{
	int		i;
	char	*matched_str;

	i = 0;
	matched_str = env_get(envp, key, 1);
	while (envp[i])
	{
		if (matched_str && envp[i] == matched_str)
			return (i);
		else if (!matched_str && *envp[i] == '\0')
			return (i);
		++i;
	}
	return (-1);
}

static int	env_pushback(t_shell *shell, char *pair)
{
	char	**new_envp;
	int		len;

	len = 0;
	while (shell->envp[len] && *shell->envp[len])
		++len;
	new_envp = (char **)ft_calloc(1, (len + 2) * sizeof(char *));
	if (!new_envp)
		return (0);
	ft_memcpy(new_envp, shell->envp, len * sizeof(char *));
	new_envp[len] = pair;
	free(shell->envp);
	shell->envp = new_envp;
	return (1);
}

static int	env_set_helper(
	t_shell *shell,
	char *res,
	int index
)
{
	if (index == -1)
	{
		if (!env_pushback(shell, res))
			return (ft_free_null_ret(&res, 0));
	}
	else
	{
		free(shell->envp[index]);
		shell->envp[index] = res;
	}
	return (1);
}

static int	env_add(t_shell *shell, int index, char *res)
{
	if (index == -1)
	{
		if (!env_pushback(shell, res))
			return (ft_free_null_ret(&res, 0));
	}
	else
	{
		if (ft_strchr(shell->envp[index], '='))
		{
			free(shell->envp[index]);
			shell->envp[index] = res;
		}
	}
	return (1);
}

/**
 * Function to set a new variable inside the env list 
 * 
 * Description:
 * 
 * -	len = len(key) + len('=') + len(value) + len('\0');
 */
int	env_set(t_shell *shell, char *key, char *value)
{
	size_t	len;
	int		index;
	char	*res;

	len = ft_strlen(key) + ft_strlen(value) + 2;
	res = (char *)ft_calloc(1, len);
	if (!res)
		return (0);
	ft_strlcat(res, key, len);
	if (value)
	{
		ft_strlcat(res, "=", len);
		ft_strlcat(res, value, len);
	}
	index = env_get_index(shell->envp, key);
	return (env_add(shell, index, res));
}

int	env_set_none(t_shell *shell, char *key)
{
	size_t	len;
	int		index;
	char	*res;

	len = ft_strlen(key) + 1;
	res = (char *)ft_calloc(1, len);
	if (!res)
		return (0);
	ft_strlcat(res, key, len);
	index = env_get_index(shell->envp, key);
	if (index == -1)
	{
		if (!env_pushback(shell, key))
			return (ft_free_null_ret(&res, 0));
	}
	else
	{
		free(shell->envp[index]);
		shell->envp[index] = res;
	}
	return (1);
}
