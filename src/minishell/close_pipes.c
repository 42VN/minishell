/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:50:02 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/14 16:59:51 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

static int	close_all_pipes(int **pipes, int num_of_pipes)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < num_of_pipes)
	{
		if (close(pipes[i][0]) < 0)
		{
			perror("minishell: close");
			status = -1;
		}
		if (close(pipes[i][1]) < 0)
		{
			perror("minishell: close");
			status = -1;
		}
		i++;
	}
	return (status);
}

int	close_pipes(t_executor *executor)
{
	int	status;

	status = 0;
	if (executor->pipes == NULL)
		return (0);
	if (close_all_pipes(executor->pipes, executor->num_of_pipes) == -1)
		return (-1);
	ft_array_delete(\
		(void *)executor->pipes, \
		sizeof(int *), \
		executor->num_of_pipes, \
		free \
	);
	executor->pipes = NULL;
	executor->num_of_pipes = 0;
	return (status);
}
