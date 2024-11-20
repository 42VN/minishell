/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:01:21 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/20 11:26:33 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exp_valid_dollar_var(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

void	exp_strip_quotes(char *str)
{
	size_t	read;
	size_t	write;
	char	quote;

	read = 0;
	write = 0;
	while (str[read])
	{
		// If the current character is a quote
		if (str[read] == '\"' || str[read] == '\'')
		{
			quote = str[read++];
			// Process until matching quote is found or end of string
			while (str[read] && str[read] != quote)
				str[write++] = str[read++];
			if (str[read] == quote)
				read++; // Skip closing quote
		}
		else
		{
			// Copy unquoted characters directly
			str[write++] = str[read++];
		}
	}
	// Null-terminate the final result
	str[write] = '\0';
}
