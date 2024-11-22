/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 23:44:03 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/26 16:56:32 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "io.h"
#include "utils.h"

static int	init_io_list(t_list *list, char *str)
{
	char	*start;
	char	*end;
	t_io	*io;

	find_redirect_op(str, &start, &end);
	if (start == NULL || end == NULL)
		return (0);
	io = new_io(start, *start);
	if (io == NULL)
		return (-1);
	if (ft_list_push(list, io) < 0)
		return (delete_io(io), -1);
	ft_memset(start, ' ', end - start);
	return (init_io_list(list, str));
}

static int	init_cmd(t_command *cmd, char *str)
{
	cmd->io_list = ft_list(0);
	if (cmd->io_list == NULL)
		return (-1);
	if (init_io_list(cmd->io_list, str) < 0)
		return (-1);
	cmd->argv = parse_cmd(str);
	if (cmd->argv == NULL)
		return (-1);
	cmd->is_builtin = check_builtin(cmd->argv[0]);
	return (0);
}

t_command	*new_cmd(const char *str)
{
	char		*dup_str;
	t_command	*cmd;

	dup_str = ft_strdup(str);
	if (dup_str == NULL)
		return (NULL);
	cmd = (t_command *)ft_calloc(1, sizeof(t_command));
	if (cmd == NULL)
	{
		free(dup_str);
		return (NULL);
	}
	if (init_cmd(cmd, dup_str) < 0)
	{
		free(dup_str);
		delete_cmd(cmd);
		return (NULL);
	}
	free(dup_str);
	return (cmd);
}
