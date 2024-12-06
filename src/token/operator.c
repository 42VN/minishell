/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:30:30 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/06 15:39:56 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Count the consecutive occurrences of the operator `op` and skip them
 */
static int	ft_count_op_skip(char **str, char op)
{
	int		count;
	char	*ptr;

	count = 0;
	ptr = *str;
	while (*ptr == op)
	{
		ptr++;
		count++;
	}
	*str = ptr;
	return (count);
}

/**
 * Check if the current token is a logical operator (&& or ||).
 * 
 */
static int	ft_token_is_logic(
	char **str,
	t_shell *shell,
	size_t *index,
	char op)
{
	int	count;

	if (!ft_token_logic_precheck(shell, *str, *index))
		return (0);
	count = ft_count_op_skip(str, **str);
	if (count == 2 && op == '&')
	{
		shell->tokens->array[*index].type = AND;
		shell->tokens->cur_pos++;
	}
	else if (op == '|' && (count == 1 || count == 2))
	{
		if (count == 1)
			shell->tokens->array[*index].type = PIPE;
		else if (count == 2)
			shell->tokens->array[*index].type = OR;
		shell->tokens->cur_pos++;
	}
	else
		return (ft_syntax_err_ret(shell, ERR_SYNTAX_LOGIC, 0));
	if (!ft_token_logic_postcheck(shell, *str))
		return (0);
	return (1);
}

/**
 * Check if the current token is a bracket ( or ).
 */
static int	ft_token_is_bracket(
	char **str,
	t_shell *shell,
	size_t	*index)
{
	if (!ft_token_bracket_check(shell, *str, *index))
		return (0);
	if (**str == '(')
	{
		shell->tokens->array[*index].type = BR_OPEN;
		shell->tokens->br_open++;
	}
	else if (**str == ')')
	{
		shell->tokens->array[*index].type = BR_CLOSE;
		shell->tokens->br_open--;
	}
	(*str)++;
	if (!ft_token_increment_pos(shell))
		return (0);
	return (1);
}

/**
 * Check if the current token is a redirection operator (< or >) and handle it.
 * 
 * Desciption:
 * 
 * -	After finding a valid redirection character(s),
 * check if the followed path is valid before making a <t_redirection> struct 
 */
static int	ft_token_is_redirect(
	char **str,
	t_shell *shell,
	size_t *index)
{
	int				count;
	char			op;
	t_redirect		*redirect;

	if (!ft_token_redirect_precheck(shell, *str))
		return (0);
	op = **str;
	shell->tokens->array[*index].type = CMD;
	count = ft_count_op_skip(str, op);
	if (count == 2 || count == 1)
	{
		ft_skip_strchr(str, ' ');
		if (!ft_redirect_check_path(shell, *str))
			return (0);
		redirect = ft_token_redirect(shell, str, op, count);
		if (!redirect)
		{
			if (shell->err_type == ERR_MALLOC)
				return (0);
			return (ft_syntax_err_ret(shell, ERR_SYNTAX_RD, 0));
		}
		ft_redirect_append(&shell->tokens->array[*index].redirect, redirect);
		return (1);
	}
	return (ft_syntax_err_ret(shell, ERR_SYNTAX_RD, 0));
}

/**
 * Function to check if the current input character is an operator.
 */
int	ft_token_handle_op(char **ptr, t_shell *shell)
{
	size_t	*index;

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
		return (ft_token_is_logic(ptr, shell, index, **ptr));
	return (0);
}
