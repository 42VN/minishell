/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:33:30 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/03 01:21:25 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_token_init(t_shell *shell)
{
	if (!shell)
		return (0);
	shell->tokens = ft_calloc(1, sizeof(t_tokens));
	if (!shell->tokens)
		return (ft_error_ret("tokenize: ft_token_init: malloc",
				shell, ERR_MALLOC, 0));
	shell->tokens->size = 5;
	shell->tokens->to_add = 5;
	shell->tokens->cur_pos = 0;
	shell->tokens->syntax_err = ERR_SYNTAX_NONE;
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
		if (!ft_token_handle_op(input, shell))
			return (0);
	}
	else
	{
		if (!ft_token_handle_cmd(input, shell))
			return (0);
	}
	return (1);
}

static int	ft_token_split_cmd(t_shell *shell)
{
	size_t	index;

	index = 0;
	while (index <= shell->tokens->cur_pos)
	{
		if (shell->tokens->array[index].cmd)
		{
			shell->tokens->array[index].split_cmd = ft_split_quote(shell->tokens->array[index].cmd, ' ');
			if (!shell->tokens->array[index].split_cmd)
				return (ft_error_ret("ft_split_cmd: malloc", shell, ERR_MALLOC, 0));
		}
		index++;
	}
	return (1);
}

static int	ft_token_post_process(t_shell *shell, char **line)
{
	if (shell->tokens->cur_pos >= 1
		&& shell->tokens->array[shell->tokens->cur_pos].type == NONE)
		shell->tokens->cur_pos--;
	if (shell->err_type == ERR_NONE &&  shell->tokens->br_open > 0)
	{
		ft_syntax_err_ret(shell, ERR_SYNTAX_BR, 0);
	}
	if (shell->err_type == ERR_SYNTAX)
	{
		ft_token_syntax_err(shell, *line);
		return (0);
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
		while (ft_isspace(*line))
			line++;
		if (*line)
		{
			if (!ft_token_add(shell, &line))
			{
				break ;
			}
		}
	}
	if (ft_token_post_process(shell, &line) == 0)
		return (0);
	if (!ft_token_split_cmd(shell))
		return (0);
	return (1);
}
