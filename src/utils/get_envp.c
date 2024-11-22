/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:30:11 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/02 22:23:14 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char *const	*get_envp(t_list *env_list)
{
	char	**envp;
	size_t	i;
	t_node	*node;

	if (env_list == NULL || env_list->length == 0)
		return (NULL);
	envp = (char **)ft_calloc(env_list->length + 1, sizeof(char *));
	if (envp == NULL)
		return (NULL);
	i = 0;
	node = env_list->head;
	while (node != NULL)
	{
		envp[i++] = (char *)node->data;
		node = node->next;
	}
	return ((char *const *)envp);
}
