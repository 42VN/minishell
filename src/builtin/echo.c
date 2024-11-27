/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:40:06 by hitran            #+#    #+#             */
/*   Updated: 2024/11/27 15:53:30 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(char **token)
{
	int	index;
	int	j;
	int	newline;

	newline = 1;
	index = 1;
	while (token[index] && !ft_strncmp(token[index], "-n", 2))
	{
		j = 1;
		while (token[index][j] == 'n')
			j++;
		if (token[index][j])
			break ;
		newline = 0;
		index++;
	}
	while (token[index])
	{
		printf("%s", token[index++]);
		if (token[index] != NULL)
			printf(" ");
	}
	if (newline)
		printf("\n");
}
