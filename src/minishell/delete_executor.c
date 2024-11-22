/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_executor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 20:09:53 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/14 16:38:13 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "command.h"

void	delete_executor(void *executor_ptr)
{
	t_executor	*ex;

	ex = (t_executor *)executor_ptr;
	if (ex == NULL)
		return ;
	if (ex->cmd_list != NULL)
		ft_list_clear(&ex->cmd_list, delete_cmd);
	free(ex->pids);
	if (ex->pipes != NULL)
	{
		close_pipes(ex);
		ft_array_delete(ex->pipes, sizeof(int *), ex->num_of_pipes, free);
	}
	free(ex);
}
