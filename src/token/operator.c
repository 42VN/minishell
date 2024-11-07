/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:30:30 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/07 21:40:10 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Count the consecutive occurrences of the operator `op` and skip them
 */
static int	ft_count_op_skip(char **str, char op)
{
	int	count;

	count = 0;
	while (**str == op)
	{
		if (count == 2 && (ft_is_op_redirect(op) || ft_is_op_logic(op)))
			return (0);
		(*str)++;
		count++;
	}
	while (ft_isspace(**str))
		(*str)++;
	if (**str && ft_is_op(**str))
	{
		if (ft_is_op_logic(op) && ft_is_op_logic(**str))
			return (0);
		else if (ft_is_op_redirect(op))
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

	if (!str || !*str || (**str != '&' && **str != '|'))
		return (0);
	op = **str;
	count = ft_count_op_skip(str, **str);
	if (count == 2 && op == '&')
	{
		shell->tokens->array[*index].type = AND;
		shell->tokens->is_cmd = 1;
		shell->tokens->cur_pos++;
		return (1);
	}
	else if (op == '|' && (count == 1 || count == 2))
	{
		if (count == 1)
			shell->tokens->array[*index].type = PIPE;
		else if (count == 2)
			shell->tokens->array[*index].type = OR;
		shell->tokens->is_cmd = 1;
		shell->tokens->cur_pos++;
		return (1);
	}
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
	if (!str || !*str || (**str != '(' && **str != ')'))
		return (0);
	if (**str == '(')
	{
		if (!ft_check_op_bracket(*str, shell, *index))
			return (0);
		shell->tokens->array[*index].type = BR_OPEN;
		shell->tokens->br_open++;
	}
	else if (**str == ')')
	{
		if (shell->tokens->br_open <= 0)
			return (0);
		if (*index > 0 && shell->tokens->array[*index - 1].type == BR_OPEN)
			return (0);
		shell->tokens->array[*index].type = BR_CLOSE;
		shell->tokens->br_open--;
	}
	(*str)++;
	if (!*str && shell->tokens->br_open != 0)
		return (0);
	if (!ft_token_increment_pos(shell))
		return (0);
	return (1);
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

	if (!str || !*str || (**str != '>' && **str != '<'))
		return (0);
	op = **str;
	if (op == '<' || op == '>')
	{
		shell->tokens->array[*index].type = CMD;
		count = ft_count_op_skip(str, op);
		if (count == 2 || count == 1)
		{
			redirect = ft_token_redirect(shell, str, op, count);
			if (!redirect)
				return (0);
			ft_redirect_append(
				&shell->tokens->array[*index].redirect,
				redirect);
			return (1);
		}
	}
	return (0);
}

/**
 * Function to check if the current input character is an operator.
 */
int	ft_token_handle_op(char **ptr, t_shell *shell)
{
	size_t	*index;
	int		result;

	if (!ptr || !*ptr || !**ptr || !shell)
		return (0);
	if (!ft_check_op(shell, *ptr))
		return (0);
	index = &shell->tokens->cur_pos;
	if (**ptr == '>' || **ptr == '<')
		return (ft_token_is_redirect(ptr, shell, index));
	if (**ptr == '(' || **ptr == ')')
		return (ft_token_is_bracket(ptr, shell, index));
	if (**ptr == '&' || **ptr == '|')
	{
		if (!ft_token_is_logic(ptr, shell, index))
			return (0);
		if (ft_token_is_last(*ptr))
			return (0);
		return (1);
	}
	return (0);
}
