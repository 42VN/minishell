/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_key_exist_v2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:27:03 by mito              #+#    #+#             */
/*   Updated: 2024/06/27 17:27:55 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static t_bool	handle_equal_sign(char *key, char *env_var)
{
	const char	*env_var_eq = ft_strchr(env_var, '=');
	const char	*key_eq = ft_strchr(key, '=');
	size_t		length;

	if (key_eq == NULL)
	{
		length = ft_strlen(key);
		if (
			((env_var_eq - env_var) == (int)length)
			&& ft_strncmp(env_var, key, length) == 0
		)
			return (true);
		return (false);
	}
	if (
		(env_var_eq - env_var) == (key_eq - key)
		&& ft_strncmp(env_var, key, (env_var_eq - env_var)) == 0
	)
		return (true);
	return (false);
}

t_bool	is_key_exist_v2(t_node *node, void *data)
{
	const char	*env_var = (const char *)node->data;
	const char	*key = (const char *)data;

	if (
		ft_strchr(env_var, '=') == NULL
		&& ft_strchr(key, '=') == NULL
	)
	{
		if (ft_strcmp(env_var, key) == 0)
			return (true);
		return (false);
	}
	return (handle_equal_sign((char *)data, (char *)node->data));
}
