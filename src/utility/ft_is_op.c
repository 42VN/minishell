/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:28:18 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/27 16:20:56 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Function to check if the current input character is an operator
 */
int	ft_is_op(char c)
{
	if (c == '>' || c == '<')
		return (1);
	if (c == '(' || c == ')')
		return (1);
	if (c == '&' || c == '|')
		return (1);
	return (0);
}

int	ft_is_op_redirect(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	ft_is_op_logic(char c)
{
	if (c == '&' || c == '|')
		return (1);
	return (0);
}

int	ft_is_op_bracket(char c)
{
	if (c == '(' || c == ')')
		return (1);
	return (0);
}
