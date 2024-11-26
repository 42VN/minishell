/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:04:21 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/25 17:24:24 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_shift_to_end(char **ptr)
{
	while (**ptr)
		(*ptr)++;
}

/**
 * Helper function for ft_token_is_logic to signify the next token will be a command
 */
void	ft_token_logic_next_cmd(t_shell *shell)
{
	shell->tokens->is_cmd = 1;
	shell->tokens->cur_pos++;
}
