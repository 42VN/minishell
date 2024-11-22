/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:44:57 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/13 22:32:10 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*resolve_env(const char *key, size_t n, t_minishell *minishell)
{
	t_node	*node;
	char	*ptr;

	if (n == 1 && ft_strncmp(key, "?", 1) == 0)
		return (minishell->exit_status_str);
	node = minishell->env_list->head;
	while (node != NULL)
	{
		ptr = ft_strchr(node->data, '=');
		if (
			n == (size_t)(ptr - (char *)node->data)
			&& ft_strncmp(key, node->data, n) == 0
		)
			return (ptr + 1);
		node = node->next;
	}
	return (NULL);
}
