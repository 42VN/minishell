/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   categorize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:38:44 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/20 16:46:04 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Handles operator tokens
 */
static void	ft_token_op_handler(
	char **input,
	char **start,
	t_token_type *type,
	t_shell *shell)
{
	while (ft_token_is_op(*input, type))
	{
		(*input)++;
		(*start)++;
	}
	if (**input != '\0')
	{
		if (ft_isspace(**input))
			*type = CMD;
		while (**input)
			(*input)++;
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
		ft_skip_quote((const char **)input, 1);
	else
	{
		while (**input && !ft_token_is_op(*input, NULL))
			(*input)++;
	}
}

/**
 * Categorizes and adds the token to the shell's token array
 */
int	ft_token_categorize(t_shell *shell, char *input, char *start)
{
	size_t			token_len;
	t_token_type	type;
	char			*str;
	size_t			index;

	while (input && *input == ' ')
		input++;
	if (ft_token_is_op(input, &type))
		ft_token_op_handler(&input, &start, &type, shell);
	else
		ft_token_cmd_handler(&input, &type);
	ft_token_print(shell);
	token_len = input - start;
	index = shell->tokens->cur_pos;
	if (type == CMD)
	{
		str = ft_substr(start, 0, token_len);
		if (index > 0)
		{
			if (!ft_token_join_cmd(&shell->tokens->array[index - 1], str))
			{
				ft_token_free(shell);
				free(str);
				return (ft_error_ret("ft_token_categorize: malloc", shell, ERR_MEMORY, 0));
			}
			free(str);
		}
		else
		{
			shell->tokens->array[index].cmd = str;
			shell->tokens->cur_pos++;
		}
	}
	else
		shell->tokens->cur_pos++;
	shell->tokens->array[shell->tokens->cur_pos].type = type;
	return (1);
}


