/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:15:49 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/10 17:24:07 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_token_free(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->tokens)
		return;
	while (i < shell->tokens->size && shell->tokens->array)
	{
		free(shell->tokens->array[i++].str);
	}
	free(shell->tokens->array);
	free(shell->tokens);
	shell->tokens = NULL;
}
