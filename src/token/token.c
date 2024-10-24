/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:33:30 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/13 14:28:27 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include "../../include/minishell.h"

static int	ft_token_init(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell)
		return (0);
	shell->tokens = ft_calloc(1, sizeof(t_tokens));
	if (!shell->tokens)
		return (ft_error_ret("tokenize: ft_token_init: malloc",
				shell, ERR_MALLOC, 0));
	shell->tokens->size = 5;
	shell->tokens->to_add = 5;
	shell->tokens->cur_pos = 0;
	shell->tokens->cur_token = 0;
	shell->tokens->is_cmd = 1;
	shell->tokens->array
		= (t_token *)ft_calloc(shell->tokens->size, sizeof(t_token));
	if (!shell->tokens->array)
	{
		shell->err_type = ERR_MALLOC;
		return (ft_error_ret("tokenize: ft_token_init: malloc",
				shell, ERR_MALLOC, 0));
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
int	ft_token_add(t_shell *shell, char **input)
{
	if (!ft_token_realloc(shell))
		return (0);
	if (ft_is_op(**input))
	{
		// printf("OP is: %s\n", *input);
		if (!ft_token_handle_op(input, shell))
		{
			ft_token_parse_error(*input);
			return (0);
		}
	}
	else
	{
		// printf("CMD is: %s\n", *input);
		if (!ft_token_handle_cmd(input, shell))
		{
			ft_token_parse_error(*input);
			return (0);
		}
	}
	return (1);
}


int	tokenize(t_shell *shell, char *line)
{
	if (!shell || !line || !*line)
		return (0);
	if (!ft_token_init(shell))
		return (0);
	while (*line)
	{
		ft_skip_strchr(&line, ' ');
		if (*line && !ft_token_add(shell, &line))
			return (0);
	}
	if (shell->tokens->array[shell->tokens->cur_pos].type == NONE)
		shell->tokens->cur_pos--;
	return (1);
}
