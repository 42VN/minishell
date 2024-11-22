/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_underscore_var.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:11:47 by mito              #+#    #+#             */
/*   Updated: 2024/06/27 17:59:12 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "minishell.h"

int	update_underscore_var(t_minishell *minishell)
{
	t_list *const	cmd_list = minishell->executor->cmd_list;
	t_command		*cmd;
	size_t			count;

	if (cmd_list == NULL || cmd_list->length > 1)
		return (0);
	cmd = (t_command *)cmd_list->head->data;
	if (cmd == NULL || cmd->argv[0] == NULL)
		return (0);
	count = count_str_array(cmd->argv);
	if (update_env("_", cmd->argv[count - 1], minishell->env_list) < 0)
		return (-1);
	return (0);
}
