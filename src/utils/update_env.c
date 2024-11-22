/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:33:35 by mito              #+#    #+#             */
/*   Updated: 2024/06/27 17:28:52 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	update_env(const char *key, const char *value, t_list *list)
{
	t_node	*node;
	char	*new_env;

	node = ft_list_find(list, (void *)key, is_key_exist_v2);
	if (node == NULL)
		return (0);
	new_env = ft_join_strings(3, key, "=", value);
	if (new_env == NULL)
		return (-1);
	free(node->data);
	node->data = new_env;
	return (0);
}

int	update_env_cd(const char *key, const char *value, t_list *list)
{
	t_node	*node;
	char	*new_env;

	node = ft_list_find(list, (void *)key, is_key_exist_v2);
	new_env = ft_join_strings(3, key, "=", value);
	if (new_env == NULL)
		return (-1);
	if (node == NULL)
	{
		if (ft_list_push(list, new_env) < 0)
			return (-1);
		return (0);
	}
	free(node->data);
	node->data = new_env;
	return (0);
}
