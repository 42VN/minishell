/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_logical_op.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:28:06 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/20 15:19:50 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*find_and_logical(const char *str)
{
	char	quote;
	int		depth;

	quote = 0;
	depth = 0;
	while (*str != '\0')
	{
		if (*str == '"' || *str == '\'')
		{
			if (quote == 0)
				quote = *str;
			else if (quote == *str)
				quote = 0;
		}
		if (*str == '(' && quote == 0)
			depth++;
		if (*str == ')' && quote == 0)
			depth--;
		if (*str == '&' && *(str + 1) == '&' && depth == 0 && quote == 0)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

char	*find_or_logical(const char *str)
{
	char	quote;
	int		depth;

	quote = 0;
	depth = 0;
	while (*str != '\0')
	{
		if (*str == '"' || *str == '\'')
		{
			if (quote == 0)
				quote = *str;
			else if (quote == *str)
				quote = 0;
		}
		if (*str == '(' && quote == 0)
			depth++;
		if (*str == ')' && quote == 0)
			depth--;
		if (*str == '|' && *(str + 1) == '|' && depth == 0 && quote == 0)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

char	*find_logical_op(const char *str)
{
	char	quote;
	int		depth;

	quote = 0;
	depth = 0;
	while (*str != '\0')
	{
		if (*str == '"' || *str == '\'')
		{
			if (quote == 0)
				quote = *str;
			else if (quote == *str)
				quote = 0;
		}
		if (*str == '(' && quote == 0)
			depth++;
		if (*str == ')' && quote == 0)
			depth--;
		if (*str == '&' && *(str + 1) == '&' && depth == 0 && quote == 0)
			return ((char *)str);
		if (*str == '|' && *(str + 1) == '|' && depth == 0 && quote == 0)
			return ((char *)str);
		str++;
	}
	return (NULL);
}
