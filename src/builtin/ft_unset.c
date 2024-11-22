/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:48:28 by mito              #+#    #+#             */
/*   Updated: 2024/06/27 17:29:50 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

int	ft_unset(t_command *cmd, t_list *env_list, t_list *export_list)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	while (cmd->argv[i] != NULL)
	{
		if (!is_valid_env_key(cmd->argv[i]))
		{
			ft_fprintf(
				2,
				"minishell: unset: `%s': not a valid identifier\n",
				cmd->argv[i]
				);
			exit_status = 1;
		}
		else
		{
			ft_list_remove(env_list, cmd->argv[i], is_key_exist_v2, free);
			ft_list_remove(export_list, cmd->argv[i], is_key_exist_v2, free);
		}
		i++;
	}
	return (exit_status);
}
