/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_env_key.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:49:31 by mito              #+#    #+#             */
/*   Updated: 2024/05/24 15:53:43 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static t_bool	has_valid_characters(const char *str)
{
	while (*str != '\0')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (false);
		str++;
	}
	return (true);
}

t_bool	is_valid_env_key(const char *str)
{
	if (
		ft_isdigit(*str)
		|| *str == '\0'
		|| ft_has_space(str)
		|| !has_valid_characters(str)
	)
		return (false);
	return (true);
}
