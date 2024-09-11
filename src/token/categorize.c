/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   categorize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:38:44 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/11 11:23:45 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/**
 * Function to check if the current input character is an operator
 */
int	ft_token_is_op(char *input)
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

static void	ft_token_op_handler(char *input, t_token_type *type)
{
	if (*input == '|')
		*type = PIPE;
	else if (*input == '>')
	{
		*type = (*input == '>') ? RD_HEREDOC : RD_OUT;
		input++;
	}
	else if (*input == '<')
		*type = RD_IN;
	else if (*input == '&')
		*type = BACKGROUND;
	else if (*input == ';')
		*type = SEMICOLON;
}

/**
 * Function to handle command and argument tokens.
 * 
 * Description: Command arguments are grouped into a single token.
 */
static void	ft_token_cmd_handler(
	char **input,
	t_token_type *type,
	int is_cmd)
{
	char	input_val;
	
	input_val = **input;
	if (is_cmd)
		*type = CMD;
	else
		*type = ARG;
	if (input_val == '"' || input_val == '\'')
	{
		ft_skip_quote(*input);
	}
	else
	{
		while (**input && !ft_token_is_op(*input))
			(*input)++;
	}
}

/**
 * Function to categorize and add the token to the shell's token array
 */
int	ft_token_categorize(
	t_shell *shell,
	char *input,
	char *start,
	int *is_cmd)
{
	size_t			token_len;
	t_token_type	type;

	if (ft_token_is_op(input))
	{
		ft_token_op_handler(input, &type);
		*is_cmd = 1;
	}
	else
	{
		ft_token_cmd_handler(&input, &type, is_cmd);
		*is_cmd = 0;
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
