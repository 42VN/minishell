/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:15:49 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/22 11:43:39 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_token_free(t_shell *shell)
{
	size_t	i; //trung

	if (!shell->tokens || !shell->tokens->array)
		return ;
	i = 0;
	while (i < shell->tokens->size)
	{
		if (shell->tokens->array[i].cmd)
		{
			free(shell->tokens->array[i].cmd);
			shell->tokens->array[i].cmd = NULL;
		}
		if (shell->tokens->array[i].split_cmd)
			ft_multi_free_null(&shell->tokens->array[i].split_cmd);
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
