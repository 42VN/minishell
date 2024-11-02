/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:12:46 by hitran            #+#    #+#             */
/*   Updated: 2024/11/02 15:03:05 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_status(t_shell *shell, int new_status)
{
	if (new_status >=  0)
		shell->exitcode = new_status;
	return (shell->exitcode);
}

void	ft_free_triptr(char ***str)
{
	int	i;

	i = 0;
	if (*str)
	{
		while ((*str)[i] != NULL)
			free((*str)[i++]);
		free(*str);
		*str = NULL;
	}
}

pid_t	init_child(t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		fork_error(shell);
	return (pid);
}

void	create_pipe(int *pipe_id)
{
	if (pipe(pipe_id) == -1)
	{
		perror("Error: pipe");
		exit (1);
	}
}

void	redirect_fd(int from_fd, int to_fd)
{
	if (dup2(from_fd, to_fd) == -1)
	{
		perror("Error: dup2");
		close(from_fd);
		exit(1);
	}
	close(from_fd);
}
