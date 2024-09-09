/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:18:52 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/13 17:29:03 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_set_null(char **str)
{
	free(*str);
	*str = NULL;
}

void	ft_multiple_free_set_null(char ***str)
{
	int	i;

	i = 0;
	if (*str)
	{
		while ((*str)[i] != NULL)
		{
			free((*str)[i]);
			i++;
		}
		free(*str);
		*str = NULL;
	}
}

char	*ft_return_multiple_free_set_null(char ***str)
{
	int	i;

	i = 0;
	if (*str)
	{
		while ((*str)[i] != NULL)
		{
			free((*str)[i]);
			i++;
		}
		free(*str);
		*str = NULL;
	}
	return (NULL);
}
