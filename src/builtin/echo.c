/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:40:06 by hitran            #+#    #+#             */
/*   Updated: 2024/10/28 21:10:47 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **token)
{
	int	index;

	index = 1;
	if (token[1] && !ft_strcmp(token[1], "-n"))
		index++;
	while (token[index])
	{
		printf("%s", token[index++]);
		if (token[index] != NULL)
			printf(" ");
	}
	if (token[1] && ft_strcmp(token[1], "-n"))
		printf("\n");
	return (1);
}
