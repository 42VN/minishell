/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   categorize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:38:44 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/13 12:15:07 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

inline static void	ft_check_redirect(
	char **input,
	t_token_type *type,
	char *input_val)
{
	if (*input_val == '>')
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
	{
		if (*(input_val + 1) == '<')
		{
			*type = RD_APPEND;
			(*input)++;
		}
		else
			*type = RD_IN;
	}
}

static void	ft_token_op_check(
	char **input,
	t_token_type *type
)
{
	char	*input_val;

	while (**input == ' ')
		(*input)++;
	input_val = *input;
	if (*input_val == '|')
		*type = PIPE;
	else if (*input_val == '>' || *input_val == '<')
	{
		ft_check_redirect(input, type, input_val);
	}
	else if (*input_val == '(')
		*type = BRACKET_OPEN;
	else if (*input_val == ')')
		*type = BRACKET_CLOSE;
	(*input)++;
}

/**
 * Handles operator tokens
 */
static void	ft_token_op_handler(
	char **input,
	t_token_type *type,
	t_shell *shell)
{
	ft_token_op_check(input, type);
	if (**input != '\0')
	{
		*type = CMD;
		while (**input)
			(*input)++;
		return ;
	}
	if (shell->tokens->need_join == 0)
	{
		if (*type == RD_IN || *type == RD_OUT || *type == RD_HEREDOC)
		{
			shell->tokens->need_join = 1;
		}
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

	while (**input == ' ')
		(*input)++;
	input_val = **input;
	*type = CMD;
	if (input_val == '"' || input_val == '\'')
		ft_skip_quote((const char **)input);
	else
	{
		while (**input && !ft_token_is_op(*input))
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
	shell->tokens->array[shell->tokens->cur_pos].str
		= ft_substr(start, 0, token_len);
	if (!shell->tokens->array[shell->tokens->cur_pos].str)
	{
		ft_token_free(shell);
		return (ft_error_ret("malloc", shell, ERR_MEMORY, 0));
	}
	shell->tokens->array[shell->tokens->cur_pos].type = type;
	shell->tokens->cur_pos++;
	return (1);
}
