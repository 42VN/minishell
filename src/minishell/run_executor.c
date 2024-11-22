/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:26:05 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/27 18:03:25 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include "minishell.h"
#include "constants.h"
#include "utils.h"
#include "minishell_signal.h"

static int	dup_pipes(int **pipes, int pipe_rw[], int pro_idx, int pid_count)
{
	pipe_rw[0] = INT_MIN;
	pipe_rw[1] = INT_MIN;
	if (pipes != NULL && pro_idx > 0)
		pipe_rw[0] = dup(pipes[pro_idx - 1][0]);
	if (pipes != NULL && pro_idx < pid_count - 1)
		pipe_rw[1] = dup(pipes[pro_idx][1]);
	if (pipe_rw[0] == -1 || pipe_rw[1] == -1)
		return (-1);
	return (0);
}

static int	run_on_current_process(t_command *cmd, t_minishell *minishell)
{
	int	exit_status;

	if (expand_cmd(cmd, minishell) < 0)
		return (1);
	if (redirect(cmd->io_list, INT_MIN, INT_MIN) < 0)
		return (1);
	if (cmd->argv[0] == NULL)
		return (0);
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		write(STDOUT_FILENO, "exit\n", 5);
	exit_status = execute_command(cmd, minishell);
	if (update_underscore_var(minishell) < 0)
		return (1);
	if (dup2(minishell->stdin, STDIN_FILENO) < 0)
		return (1);
	if (dup2(minishell->stdout, STDOUT_FILENO) < 0)
		return (1);
	return (exit_status);
}

static int	run_on_sub_process(int i, t_command *cmd, t_minishell *minishell)
{
	const t_executor	*executor = minishell->executor;
	int					pipe_rw[2];
	int					exit_status;

	if (reset_signals() < 0)
		exit_on_error(NULL, NULL, minishell, 1);
	if (dup_pipes(executor->pipes, pipe_rw, i, executor->num_of_pids) < 0)
		exit_on_error("dup", strerror(errno), minishell, 1);
	close_pipes(minishell->executor);
	if (expand_cmd(cmd, minishell) < 0)
		exit_on_error(NULL, NULL, minishell, 1);
	if (redirect(cmd->io_list, pipe_rw[0], pipe_rw[1]) < 0)
		exit_on_error(NULL, NULL, minishell, 1);
	if (cmd->argv[0] == NULL)
		exit(0);
	exit_status = execute_command(cmd, minishell);
	delete_minishell(minishell);
	exit(exit_status);
}

static int	start_workers(t_executor *executor, t_minishell *minishell)
{
	const t_node	*node = executor->cmd_list->head;
	int				i;

	i = 0;
	while (i < executor->num_of_pids)
	{
		executor->pids[i] = fork();
		if (executor->pids[i] < 0)
		{
			perror("minishell: fork");
			close_pipes(executor);
			wait_all(executor->pids, executor->num_of_pids);
			return (-1);
		}
		if (executor->pids[i] == 0)
			run_on_sub_process(i, node->data, minishell);
		node = node->next;
		i++;
	}
	if (close_pipes(executor) < 0)
		return (-1);
	return (0);
}

/**
 * Run list of commands in struct `t_executor` whether in child processes or
 * in the same process that `./minishell` is running on.
 *
 * @param executor The pointer to struct `t_executor`.
 * @param minishell The pointer to struct `t_minishell`.
 *
 * @returns Exit status code between `0` and `255`. The `0` number indicates
 * 			success, non-zero number means error.
*/
int	run_executor(t_executor *executor, t_minishell *minishell)
{
	t_command	*cmd;
	int			exit_status;

	cmd = (t_command *)executor->cmd_list->head->data;
	if (executor->num_of_pids == 0)
		return (run_on_current_process(cmd, minishell));
	if (start_workers(executor, minishell) < 0)
		return (1);
	exit_status = wait_all(executor->pids, executor->num_of_pids);
	if (update_underscore_var(minishell) < 0)
		return (1);
	return (exit_status);
}
