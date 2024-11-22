/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:12:30 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/02 21:14:36 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <errno.h>

int	wait_all(pid_t *pids, int number_of_pids)
{
	pid_t	pid;
	int		wstatus;
	int		exit_status;

	exit_status = 0;
	while (1)
	{
		pid = wait(&wstatus);
		if (pid == -1 && errno == ECHILD)
			break ;
		if (pid == pids[number_of_pids - 1])
		{
			if (WIFEXITED(wstatus))
				exit_status = WEXITSTATUS(wstatus);
			else if (WIFSIGNALED(wstatus))
				exit_status = 128 + WTERMSIG(wstatus);
		}
	}
	return (exit_status);
}
