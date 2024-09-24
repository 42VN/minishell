/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:37:24 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/21 14:30:55 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int	parse(int ac, char **av, t_shell *shell)
{
	char	*clone;
	int		i;

	i = 0;
	clone = ft_av_dup(av);
	if (!clone)
		return (0);
	while (av[i])
	{
		
	}
	return (1);
}