/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:30:30 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/24 12:09:49 by ktieu            ###   ########.fr       */
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
	if (**str && ft_is_op(*str))
		return (0);
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
static int	ft_token_is_logic(char **str, t_token_type *type)
{
	int		count;
	char	op;

	op = **str;
	if (op == '&' || op == '|')
	{
		count = ft_count_op(str, op);
		if (count == 2)
		{
			if (op == '&')
				*type = AND;
			else if (op == '|')
				*type = OR;
			return (1);
		}
		else if (count == 1 && op == '|')
		{
			*type = PIPE;
			return (1);
		}
	}
	*type = INVALID;
	return (0);
}

/**
 * Check if the current token is a bracket ( or ).
 */
static int	ft_token_is_bracket(
	char **str,
	t_token_type *type)
{
	if (**str == '(')
	{
		*type = BR_OPEN;
		(*str)++;
		return (1);
	}
	else if (**str == ')')
	{
		*type = BR_CLOSE;
		(*str)++;
		return (1);
	}
	return (0);
}

/**
 * Check if the current token is a redirection operator (< or >) and handle it.
 */
static int	ft_token_is_redirect(
	char **str, 
	t_shell *shell,
	t_token_type *type,
	size_t *index)
{
	int				count;
	char			op;
	t_redirect		*redirect;

	op = **str;
	if (op == '<' || op == '>')
	{
		printf("Redirect\n");
		*type = CMD;
		count = ft_count_op(str, op);
		redirect = ft_token_redirect(shell, str, op, count);
		if (!redirect)
			return (0);
		ft_redirect_append(&shell->tokens->array[*index].redirect, redirect);
		return (1);
	}
	*type = INVALID;
	return (0);
}



/**
 * Function to check if the current input character is an operator.
 */
int	ft_token_handle_op(char **ptr, t_shell *shell)
{
	t_token_type	*type;
	size_t			*index;

	if (!ptr || !*ptr || !**ptr || !shell)
		return (0);
	index = &shell->tokens->cur_pos;
	type = &shell->tokens->array[*index].type;
	if (**ptr == '>' || **ptr == '<')
		return (ft_token_is_redirect(ptr, shell, type, index));
	if (**ptr == '(' || **ptr == ')')
		return (ft_token_is_bracket(ptr, type));
	if (**ptr == '&' || **ptr == '|')
		return (ft_token_is_logic(ptr, type));	
	return (0);
}
