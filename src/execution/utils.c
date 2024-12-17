/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:12:46 by hitran            #+#    #+#             */
/*   Updated: 2024/12/17 13:33:16 by hitran           ###   ########.fr       */
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

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		update_status(shell, WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		update_status(shell, 128 + WTERMSIG(status));
}

void	print_fault(t_shell *shell)
{
	if (shell->exitcode - 128 == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
	else if (shell->exitcode - 128 == SIGSEGV)
		ft_putendl_fd("Segmentation fault (core dumped)", STDERR_FILENO);
}

int	is_recursive(t_ast *ast)
{
	if (ast->token.cmd && (!ft_strcmp(ast->token.cmd, "./minishell") 
			|| !ft_strcmp(ast->token.cmd, "./minishell_bonus")))
		return (1);
	else
		return (0);
}
