/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:01:21 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/17 01:43:13 by ktieu            ###   ########.fr       */
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
		if (str[read] == '\"' || str[read] == '\'')
		{
			quote = str[read];
			read++;
			while (str[read] && str[read] != quote)
			{
				str[write++] = str[read++];
			}
			if (str[read] == quote)
				read++;
		}
		else
			str[write++] = str[read++];
	}
	str[write] = '\0';
}
