/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_dup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:15:51 by hitran            #+#    #+#             */
/*   Updated: 2024/08/16 15:20:55 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

char	**ft_matrix_dup(char **matrix, int row)
{
	char	**res;
	int		i;

	res = (char **)ft_calloc(row + 1, sizeof(char *));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < row)
	{
		res[i] = ft_strdup(matrix[i]);
		if (!res[i])
		{
			ft_free_triptr(&res);
			return (NULL);
		}
	}
	return (res);
}
