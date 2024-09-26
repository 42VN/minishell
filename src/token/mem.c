/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:09:42 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/26 17:25:36 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Reallocates the token array if necessary when adding new tokens
 * 
 * Description: the function only run when the array 
 * runs out of space (current index >= size)
 */
int	ft_token_realloc(t_shell *shell)
{
	t_token	*new_array;
	size_t	new_size;

	if (shell->tokens->cur_pos < shell->tokens->size)
		return (1);
	new_size = shell->tokens->size * shell->tokens->to_add;
	new_array = (t_token *)ft_calloc(new_size, sizeof(t_token));
	if (!new_array)
	{
		shell->err_type = ERR_MEMORY;
		return (0);
	}
	ft_memmove(new_array, shell->tokens->array,
		sizeof(t_token) * shell->tokens->size);
	free(shell->tokens->array);
	shell->tokens->array = new_array;
	shell->tokens->size = new_size;
	return (1);
}
