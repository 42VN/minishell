/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:07:02 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/16 10:47:06 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


inline static int	ft_token_is_rd(char *str, t_token_type *type)
{
	if (*str == '>')
	{
		if (type && (str + 1))
		{
			if (*(str + 1) == '>')
				*type = RD_HEREDOC;
			else
				*type = RD_OUT;
		}
		return (1);
	}
	else if (*str == '<')
	{
		if (type && (str + 1))
		{
			if (*(str + 1) == '<')
				*type = RD_APPEND;
			else
				*type = RD_IN;
		}
		return (1);
	}
	return (0);
}

inline static int	ft_token_is_logic(char *str, t_token_type *type)
{
	if (*str == '&')
	{
		if (type && (str + 1))
		{
			if (*(str + 1) == '&')
				*type = AND;
		}
		return (1);
	}
	else if (*str == '|')
	{
		if (type && (str + 1))
		{
			if (type && *(str + 1) == '|')
				*type = AND;
		}
		else
		{
			if (type)
				*type = PIPE;
		}
		return (1);
	}
	return (0);
}

inline static int	ft_token_is_bracket(char *str, t_token_type *type)
{
	if (*str == '(')
	{
		if (type)
			*type = BR_OPEN;
		return (1);
	}
	else if (*str == ')')
	{
		if (type)
			*type = BR_CLOSE;
		return (1);
	}
	return (0);
}

/**
 * Function to check if the current input character is an operator
 */
int	ft_token_is_op(char *str, t_token_type *type)
{
	if (!str || !*str)
		return (0);
	if (*str == '>' || *str == '<')
		return (ft_token_is_rd(str, type));
	if (*str == '(' || *str == ')')
		return (ft_token_is_bracket(str, type));
	if (*str == '&' || *str == '|')
		return (ft_token_is_logic(str, type));	
	return (0);
}
