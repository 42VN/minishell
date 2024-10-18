/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:32:02 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/18 12:39:08 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(
	t_shell *shell,
	t_builtin_type type,
	char **args)
{
	int	exit_code;

	exit_code = 0;
	if (type == BI_ENV || type == BI_EXPORT || type == BI_UNSET)
		exit_code = 0;
	shell->exitcode = exit_code;
	return (1);
}
