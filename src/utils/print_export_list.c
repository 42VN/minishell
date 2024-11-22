/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:59:43 by mito              #+#    #+#             */
/*   Updated: 2024/06/10 13:09:19 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	print_export_list(t_list *export_list)
{
	char	*eq_sign;
	t_node	*node;

	node = export_list->head;
	while (node != NULL)
	{
		if (write(1, "declare -x ", 11) < 0)
			return (1);
		eq_sign = ft_strchr((const char *)node->data, '=');
		if (eq_sign == NULL)
			printf("%s\n", (const char *)node->data);
		else
		{
			if (write(1, node->data, eq_sign - (char *)node->data + 1) < 0)
				return (1);
			if (printf("\"%s\"\n", eq_sign + 1) < 0)
				return (1);
		}
		node = node->next;
	}
	return (0);
}
