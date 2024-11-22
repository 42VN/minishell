/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:47:03 by mito              #+#    #+#             */
/*   Updated: 2024/06/27 17:29:16 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	update_shlvl(t_list *list)
{
	t_node	*node;
	char	*shlvl;
	int		shlvl_number;
	char	buf[sizeof(int) * 8 + 1];

	node = ft_list_find(list, "SHLVL", is_key_exist_v2);
	if (node == NULL)
	{
		shlvl = ft_strdup("SHLVL=1");
		if (shlvl == NULL)
			return (-1);
		if (ft_list_push(list, shlvl) < 0)
			return (-1);
		return (0);
	}
	shlvl = ft_strchr((char *)node->data, '=');
	shlvl_number = ft_atoi(shlvl + 1, NULL);
	ft_itoa(shlvl_number + 1, buf, 10);
	shlvl = ft_join_strings(2, "SHLVL=", buf);
	if (shlvl == NULL)
		return (-1);
	free(node->data);
	node->data = shlvl;
	return (0);
}
