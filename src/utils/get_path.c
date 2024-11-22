/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:30:11 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/20 13:10:56 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	**get_path(t_list *env_list)
{
	char	*path_env_value;

	path_env_value = find_env("PATH", env_list);
	if (path_env_value == NULL)
		return (NULL);
	return (ft_split(path_env_value, ':'));
}
