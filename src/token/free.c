/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:15:49 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/29 15:03:22 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include "../../include/minishell.h"

void	ft_token_free(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->tokens)
		return ;
	while (i < shell->tokens->size && shell->tokens->array)
	{
		if (shell->tokens->array[i].cmd)
		{
			free(shell->tokens->array[i].cmd);
			shell->tokens->array[i].cmd = NULL;
		}
		if (shell->tokens->array[i].redirect)
		{
			ft_redirect_clear(&shell->tokens->array[i].redirect);
			shell->tokens->array[i].redirect = NULL;
		}
		++i;
	}
	free(shell->tokens->array);
	shell->tokens->array = NULL;
	free(shell->tokens);
	shell->tokens = NULL;
}

