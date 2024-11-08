/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:12:46 by hitran            #+#    #+#             */
/*   Updated: 2024/11/08 11:00:50 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_status(t_shell *shell, int new_status)
{
	if (new_status >= 0)
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

// pid_t	init_child(t_shell *shell)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	pid = -1;//test
// 	if (pid == -1)
// 		fork_error(shell);//, NULL);
// 	return (pid);
// }

// void	create_pipe(int *pipe_id)
// {
// 	int i = pipe(pipe_id); //test
// 	i = -1; //test
// 	if (i == -1) //test pipe(pipe_id) == -1)
// 	{
// 		perror("minishell: pipe");
// 		exit (1);
// 	}
// }

void	redirect_fd(int from_fd, int to_fd)
{
	if (dup2(from_fd, to_fd) == -1)
	{
		perror("minishell: dup2");
		close(from_fd);
		exit(1);
	}
	close(from_fd);
}

void	wait_update(t_shell *shell, pid_t pid)
{
	int		status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		update_status(shell, WEXITSTATUS(status));
}
