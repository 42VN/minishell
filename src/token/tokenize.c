/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:15:01 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/10 21:35:14 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_token_init(t_shell *shell)
{
	shell->tokens->size = 10;
	shell->tokens->to_add = 10;
	shell->tokens->cur_pos = 0;
	shell->tokens->cur_token = 0;
	shell->tokens->array = (t_token *)ft_calloc(shell->tokens->size, sizeof(t_token));
	if (!shell->tokens->array)
	{
		shell->err_type = ERR_MEMORY;
		ft_free_token(shell);
		return (0);
	}
	return (1);
}



/**
 * Function that add a new token
 * Description:
 * -	Adding a new token to the allocated array
 * -	Reallocating the array if extension is needed
 * -	Changing the input by taking the pointer <p_input>
 */
int	ft_token_add(t_shell *shell, char **p_input)
{
	if (!ft_token_realloc(shell))
		return (0);
	
	return (1);
}


void	*tokenize(t_shell *shell, char *input)
{
	if (!shell || !input || !*input)
		return;
	shell->tokens = ft_calloc(1, sizeof(t_tokens));
	if (!shell->tokens)
	{
		shell->err_type = ERR_MEMORY;
		return;
	}
	if (!ft_token_init(shell))
		return;
	while (*input)
	{
		ft_skip_strchr(&input, ' ');
		if (*input)
		{
			if (!ft_token_add(shell, &input))
				break;
		}
	}
}
