/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   categorize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:38:44 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/10 21:52:14 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/**
 * Function to check if the current input character is an operator
 */
int	ft_token_is_operator(char *input)
{
	if (*input == '|')
		return (1);
	if (*input == '>')
		return (1);
	if (*input == '<')
		return (1);
	if (*input == '&')
		return (1);
	if (*input == ';')
		return (1);
	return (0);
}

/**
 * Function to categorize and add the token to the shell's token array
 */
int	ft_token_categorize(t_shell *shell, char *input, char *start)
{
	size_t	token_len;
	t_token_type	type;

	if (ft_token_is_operator(input))
	{
		if (*input == '|')
			type = PIPE;
		else if (*input == '>')
		{
			type = (*input == '>') ? RD_HEREDOC : RD_OUT;
			input++;
		}
		else if (*input == '<')
			type = RD_IN;
		else if (*input == '&')
			type = BACKGROUND;
		else if (*input == ';')
			type = SEMICOLON;
	}
	else
	{
		type = CMD;  // Default to command/argument
		while (*input && !ft_token_is_operator(input) && *input != ' ')
			input++;
	}
	token_len = input - start;
	shell->tokens->array[shell->tokens->cur_pos].str = ft_substr(start, 0, token_len);
	if (!shell->tokens->array[shell->tokens->cur_pos].str)
	{
		shell->err_type = ERR_MEMORY;
		ft_free_token(shell);
		return (0);
	}
	shell->tokens->array[shell->tokens->cur_pos].type = type;
	shell->tokens->cur_pos++;
	return (1);
}
