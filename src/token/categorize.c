/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   categorize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:38:44 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/12 15:33:57 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/**
 * Function to check if the current input character is an operator
 */
int	ft_token_is_op(char *input)
{
	if (*input == '>' || *input == '<')
		return (1);
	if (*input == '|')
		return (1);
	if (*input == '(' || *input == ')')
		return (1);
	return (0);
}

/**
 * Handles operator tokens
 */
static void	ft_token_op_handler(
	char **input,
	t_token_type *type,
	t_shell *shell)
{
	char	*input_val;

	input_val = *input;
	if (*input_val == '|')
		*type = PIPE;
	else if (*input_val == '>')
	{
		if (*(input_val + 1) == '>')
		{
			*type = RD_HEREDOC;
			(*input)++;
		}
		else
			*type = RD_OUT;
	}
	else if (*input_val == '<')
		*type = RD_IN;
	(*input)++;
	if (shell->tokens->need_join == 0)
	{
		if (*type == RD_IN || *type == RD_APPEND || *type == RD_APPEND)
			shell->tokens->need_join = 1;
	}
}

/**
 * Handles command and argument tokens
 */
static void	ft_token_cmd_handler(
	char **input,
	t_token_type *type)
{
	char	input_val;
	
	input_val = **input;
	*type = CMD;
	if (input_val == '"' || input_val == '\'')
		ft_skip_quote((const char **)input);
	else
	{
		while (**input && !ft_token_is_op(*input) && **input != ' ')
			(*input)++;	
	}
}

/**
 * Categorizes and adds the token to the shell's token array
 */
int	ft_token_categorize(
	t_shell *shell,
	char *input,
	char *start)
{
	size_t			token_len;
	t_token_type	type;

	if (ft_token_is_op(input))
		ft_token_op_handler(&input, &type, shell);
	else
		ft_token_cmd_handler(&input, &type);
	token_len = input - start;
	shell->tokens->array[shell->tokens->cur_pos].str = ft_substr(start, 0, token_len);
	if (!shell->tokens->array[shell->tokens->cur_pos].str)
	{
		shell->err_type = ERR_MEMORY;
		ft_token_free(shell);
		return (0);
	}
	shell->tokens->array[shell->tokens->cur_pos].type = type;
	shell->tokens->cur_pos++;
		return (1);
}
