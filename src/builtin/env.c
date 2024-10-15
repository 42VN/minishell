/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:49:27 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/15 16:20:08 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int export_message(char **envp)
{
	
}

int	builtin_export(t_shell *shell, char **split_cmd)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (!shell || !split_cmd || !split_cmd[0])
		return (0);
}
 