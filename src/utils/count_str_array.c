/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_str_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:53:10 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/20 13:09:17 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	count_str_array(char **str_array)
{
	int	i;

	if (str_array == NULL)
		return (0);
	i = 0;
	while (str_array[i])
		i++;
	return (i);
}
