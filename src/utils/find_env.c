/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:19:26 by mito              #+#    #+#             */
/*   Updated: 2024/06/19 23:24:07 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * The `find_env()` returns value (string part after `=` sign) of environment
 * variable that is identified by `key` string. If no matching key is found,
 * NULL is returned.
 *
*/
char	*find_env(const char *key, t_list *list)
{
	t_node	*node;
	char	*ptr;
	size_t	key_length;

	key_length = ft_strlen(key);
	node = list->head;
	while (node != NULL)
	{
		ptr = ft_strchr(node->data, '=');
		if (ptr != NULL)
		{
			if (
				key_length == (size_t)(ptr - (char *)node->data)
				&& ft_strncmp(key, node->data, key_length) == 0
			)
				return (ptr + 1);
		}
		else if (ft_strcmp(key, node->data) == 0)
			return (ptr + 1);
		node = node->next;
	}
	return (NULL);
}
