/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:30:30 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/24 14:28:27 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Count the consecutive occurrences of the operator `op`.
 */
static int	ft_count_op(char **str, char op)
{
	int		count;

	if (!str || !*str || !**str)
		return (0);
	count = 0;
	while (**str == op)
	{
		(*str)++;
		count++;
	}
	ft_skip_strchr(str, ' ');
	if (**str && ft_is_op(*str))
	{
		return (0);
	}
	return (count);
}

/**
 * Check if the current token is a logical operator (&& or ||).
 */
static int	ft_token_is_logic(
	char **str,
	t_shell *shell,
	size_t *index)
{
	int		count;
	char	op;

	op = **str;
	if (op == '&' || op == '|')
	{
		count = ft_count_op(str, op);
		if (count == 2 && op == '&')
			shell->tokens->array[*index].type = AND;
		else if (count == 2 && op == '|')
			shell->tokens->array[*index].type = OR;
		else if (count == 1 && op == '|')
			shell->tokens->array[*index].type  = PIPE;
		if (count == 2 || count == 1)
		{
			shell->tokens->is_cmd = 1;
			shell->tokens->cur_pos++;
			return (1);
		}
	}
	shell->tokens->array[*index].type  = INVALID;
	return (0);
}

/**
 * Check if the current token is a bracket ( or ).
 */
static int	ft_token_is_bracket(
	char **str,
	t_shell *shell,
	size_t	*index)
{
	if (**str == '(')
	{
		shell->tokens->array[*index].type = BR_OPEN;
		(*str)++;
		return (1);
	}
	else if (**str == ')')
	{
		shell->tokens->array[*index].type = BR_CLOSE;
		(*str)++;
		return (1);
	}
	shell->tokens->array[*index].type  = INVALID;
	return (0);
}

/**
 * Check if the current token is a redirection operator (< or >) and handle it.
 */
static int	ft_token_is_redirect(
	char **str, 
	t_shell *shell,
	size_t *index)
{
	int				count;
	char			op;
	t_redirect		*redirect;

	op = **str;
	if (op == '<' || op == '>')
	{
		shell->tokens->array[*index].type = CMD;
		count = ft_count_op(str, op);
		if (count == 2 || count == 1)
		{
			redirect = ft_token_redirect(shell, str, op, count);
			if (!redirect)
				return (0);
			ft_redirect_append(&shell->tokens->array[*index].redirect, redirect);
			return (1);
		}
	}
	shell->tokens->array[*index].type = INVALID;
	return (0);
}

/**
 * Function to check if the current input character is an operator.
 */
int	ft_token_handle_op(char **ptr, t_shell *shell)
{
	size_t			*index;

	if (!ptr || !*ptr || !**ptr || !shell)
		return (0);
	index = &shell->tokens->cur_pos;
	if (**ptr == '>' || **ptr == '<')
		return (ft_token_is_redirect(ptr, shell, index));
	if (**ptr == '(' || **ptr == ')')
	{
		if (ft_token_is_bracket(ptr, shell, index))
		{
			shell->tokens->cur_pos++;
			return (1);
		}
		return (0);
	}
	if (**ptr == '&' || **ptr == '|')
		return (ft_token_is_logic(ptr, shell, index));
	return (0);
}
