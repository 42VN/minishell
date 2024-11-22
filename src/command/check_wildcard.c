/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:28:52 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/16 13:37:27 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

/**
 * @returns `true` if the given command accepts wildcard expansion,
 * 			`false` otherwise.
*/
t_bool	check_wildcard(const char *cmd)
{
	int			i;
	const char	*cmds[] = {
		"ls", "cp", "mv", "rm", "grep", "find", "tar", "rsync", "chmod",
		"chown", "echo", "cat", "head", "tail", "mkdir", "rmdir", "ln",
		"chmod", "chown", "touch", NULL
	};

	i = 0;
	while (cmds[i] != NULL)
	{
		if (ft_strcmp(cmd, cmds[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}
