/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:26:07 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/17 12:15:47 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to pre-check for the valid of a logic operator
 * 
 * Description:
 *-		Initial check:	is a standalone
 *-		Left check:		the left token must
 either be a command or a closed bracket
 */
int	ft_token_logic_precheck(t_shell *shell, char *str, size_t index)
{
	if (*str != '|' && *str != '&')
		return (ft_syntax_err_ret(shell, ERR_SYNTAX_LOGIC, 0));
	if (index == 0 || ft_token_is_last(str))
		return (ft_syntax_err_ret(shell, ERR_SYNTAX_LOGIC, 0));
	if (index > 0 && shell->tokens->array[index - 1].type != CMD
		&& shell->tokens->array[index - 1].type != BR_CLOSE)
	{
		return (ft_syntax_err_ret(shell, ERR_SYNTAX_LOGIC, 0));
	}
	return (1);
}

/**
 * Function to post-check for the valid of a logic operator
 * 
 * Description:
 *-		Right check:	no consecutive logic operator
 */
int	ft_token_logic_postcheck(t_shell *shell, char *str)
{
	while (ft_isspace(*str))
		str++;
	if (ft_is_op_logic(*str))
		return (ft_syntax_err_ret(shell, ERR_SYNTAX_LOGIC, 0));
	return (1);
}

int	ft_token_bracket_check(t_shell *shell, char *str, size_t index)
{
	if (*str != '(' && *str != ')')
		return (ft_syntax_err_ret(shell, ERR_SYNTAX_BR, 0));
	if (*str == '(')
	{
		if (index > 0 && shell->tokens->array[index - 1].type == BR_CLOSE)
			return (ft_syntax_err_ret(shell, ERR_SYNTAX_BR, 0));
	}
	else if (*str == ')')
	{
		if (shell->tokens->br_open <= 0)
			return (ft_syntax_err_ret(shell, ERR_SYNTAX_BR, 0));
		if (index > 0 && shell->tokens->array[index - 1].type == BR_OPEN)
			return (ft_syntax_err_ret(shell, ERR_SYNTAX_BR, 0));
	}
	return (1);
}

/**
 * Function to check for the valid of a logic operator
 */
int	ft_token_redirect_precheck(t_shell *shell, char *str)
{
	if (*str != '<' && *str != '>')
		return (ft_syntax_err_ret(shell, ERR_SYNTAX_RD, 0));
	return (1);
}
