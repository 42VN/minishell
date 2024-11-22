/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_key_exist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:24:46 by mito              #+#    #+#             */
/*   Updated: 2024/06/10 15:40:46 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_bool	is_key_exist(t_node *node, void *data)
{
	const char	*ev_node = (const char *)node->data;
	const char	*en_data = (const char *)data;
	char		*env_node_eq_ptr;
	char		*en_data_eq_ptr;
	int			i;

	env_node_eq_ptr = ft_strchr(ev_node, '=');
	en_data_eq_ptr = ft_strchr(en_data, '=');
	if (en_data_eq_ptr == NULL)
	{
		i = ft_strlen(en_data);
		if (
			((env_node_eq_ptr - ev_node) == i)
			&& ft_strncmp(ev_node, en_data, i) == 0
		)
			return (true);
		return (false);
	}
	if (
		(env_node_eq_ptr - ev_node) == (en_data_eq_ptr - en_data)
		&& ft_strncmp(ev_node, en_data, (env_node_eq_ptr - ev_node)) == 0
	)
		return (true);
	return (false);
}
