/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:06:36 by mito              #+#    #+#             */
/*   Updated: 2024/06/20 17:09:21 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "builtin.h"

int	ft_env(t_command *cmd, t_list *env_list)
{
	t_node	*node;

	if (cmd->argv[1] != NULL)
	{
		ft_fprintf(
			2, "%s: %s: %s\n", cmd->argv[0],
			cmd->argv[1], "No such file or directory"
			);
		return (127);
	}
	node = env_list->head;
	while (node != NULL)
	{
		if (printf("%s\n", (char *)node->data) < 0)
			return (1);
		node = node->next;
	}
	return (0);
}
