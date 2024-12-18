/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:12:46 by hitran            #+#    #+#             */
/*   Updated: 2024/12/18 10:26:14 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		update_status(shell, WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		update_status(shell, 128 + WTERMSIG(status));
	}
	init_signals();
}

int	is_recursive(t_ast *ast)
{
	if (ast->token.cmd && (!ft_strcmp(ast->token.cmd, "./minishell")
			|| !ft_strcmp(ast->token.cmd, "./minishell_bonus")))
		return (1);
	else
		return (0);
}
