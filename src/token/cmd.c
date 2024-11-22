/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:29:53 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/22 11:45:28 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * - Handles the creation or update of command tokens. 
 * - If there is no string in the token array
 * at the current index, a new command is created.
 * - Otherwise, the string is joined as an argument to the existing command.
 */
int	ft_token_handle_cmd(char **ptr, t_shell *shell)
{
	size_t			*index;
	char			*str;

	if (!**ptr)
		return (1);
	index = &shell->tokens->cur_pos;
	if (!ft_is_op(**ptr))
	{
		str = ft_token_parse(ptr, shell, 0);
		if (!str)
			return (0);
		if (*index > 0 && shell->tokens->array[*index].type == CMD //trung
			&& shell->tokens->array[*index].cmd)
		{
			if (!ft_token_join_cmd(&shell->tokens->array[*index], &str))
				return (ft_free_null_ret(&str, 0));
		}
		else
		{
			shell->tokens->array[*index].type = CMD;
			shell->tokens->array[*index].cmd = str;
		}
		return (1);
	}
	return (0);
}
