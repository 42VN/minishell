/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:29:53 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/28 23:47:14 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_token_handle_cmd_init(t_shell *shell, char **ptr, size_t **index, char **str)
{
	if (!**ptr)
		return (1);
	if (ft_is_op(**ptr))
		return (0);
	*index = &shell->tokens->cur_pos;
	*str = ft_token_parse(ptr, shell, 0);
	if (!str)
		return (0);
	return (1);
}

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

	if (!ft_token_handle_cmd_init(shell, ptr, &index, &str))
		return (0);
	if (index && shell->tokens->array[*index].type == CMD //trung
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
