/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_env_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:45:00 by mito              #+#    #+#             */
/*   Updated: 2024/05/27 17:59:27 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_list	*clone_env_list(t_list *src_list)
{
	t_list	*clone;
	t_node	*node;
	char	*data;

	clone = ft_list(src_list->is_circular);
	if (clone == NULL)
		return (NULL);
	node = src_list->head;
	while (node != NULL)
	{
		data = ft_strdup((char *)node->data);
		if (data == NULL)
		{
			ft_list_clear(&clone, free);
			return (NULL);
		}
		ft_list_push(clone, data);
		node = node->next;
	}
	return (clone);
}
