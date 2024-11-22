/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:21:35 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/28 17:18:35 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include "minishell.h"
#include "utils.h"

static int	run(const char *str, t_minishell *minishell)
{
	t_list	*cmd_list;
	int		exit_status;

	cmd_list = parse_cmd_list(str);
	if (cmd_list == NULL)
		return (1);
	if (cmd_list->length == 0)
		return (ft_list_clear(&cmd_list, delete_cmd), 0);
	if (heredoc(cmd_list, minishell) == -1)
	{
		ft_list_clear(&cmd_list, delete_cmd);
		if (errno == EINTR)
			return (130);
		return (1);
	}
	minishell->executor = new_executor(cmd_list);
	if (minishell->executor == NULL)
		return (perror("minishell: malloc"), 1);
	exit_status = run_executor(minishell->executor, minishell);
	delete_executor(minishell->executor);
	minishell->executor = NULL;
	return (exit_status);
}

static int	execute_next(int cur_exit_status, char *str, t_minishell *mns)
{
	char	*logical_symbol;

	if (cur_exit_status == 0)
	{
		if (ft_strncmp(str, "&&", 2) == 0)
			return (execute(str + 2, mns));
		logical_symbol = find_and_logical(str + 2);
		if (logical_symbol != NULL)
			return (execute(logical_symbol + 2, mns));
	}
	if (cur_exit_status != 0)
	{
		if (ft_strncmp(str, "||", 2) == 0)
			return (execute(str + 2, mns));
		logical_symbol = find_or_logical(str + 2);
		if (logical_symbol != NULL)
			return (execute(logical_symbol + 2, mns));
	}
	return (cur_exit_status);
}

int	execute(char *str, t_minishell *minishell)
{
	char	*logical_op;
	char	*sub_str;
	int		exit_status;

	logical_op = find_logical_op(str);
	if (logical_op == NULL)
	{
		ungroup((char *)str);
		logical_op = find_logical_op(str);
	}
	if (logical_op == NULL)
		return (run(str, minishell));
	sub_str = ft_substr(str, 0, logical_op - str);
	if (sub_str == NULL)
		return (1);
	exit_status = execute(sub_str, minishell);
	free(sub_str);
	exit_status = execute_next(exit_status, logical_op, minishell);
	return (exit_status);
}
