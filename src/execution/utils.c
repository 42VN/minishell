/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:12:46 by hitran            #+#    #+#             */
/*   Updated: 2024/11/21 11:16:31 by hitran           ###   ########.fr       */
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
	else if (WIFSIGNALED(status))
		update_status(shell, 128 + WTERMSIG(status));
}

void	print_fault(t_shell *shell)
{
	if (shell->exitcode - 128 == SIGQUIT)
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	else if (shell->exitcode - 128 == SIGSEGV)
		write(STDERR_FILENO, "Segmentation fault (core dumped)\n", 33);
}
