/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_av_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:39:22 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/16 18:40:22 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_av_dup(char **av)
{
	char	**res;
	int		i;

	i = 0;
	while (av && av[i])
		++i;
	res = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (av && av[i])
	{
		res[i] = ft_strdup(av[i]);
		if (!res[i])
		{
			ft_multi_free_null(&res);
			return (NULL);
		}
		++i;
	}
	return (res);
}