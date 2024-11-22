/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_underscore_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:27:15 by mito              #+#    #+#             */
/*   Updated: 2024/06/20 15:01:25 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_underscore_var(char *cmd_arg)
{
	if (ft_starts_with(cmd_arg, "_=") == true || ft_strcmp(cmd_arg, "_") == 0)
		return (1);
	return (0);
}
