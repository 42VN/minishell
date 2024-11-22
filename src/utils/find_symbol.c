/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_symbol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:28:32 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/12 23:52:16 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*find_symbol(const char *str, const char *symbol)
{
	char	quote;
	size_t	sym_len;

	if (str == NULL || *str == '\0')
		return (NULL);
	quote = 0;
	sym_len = ft_strlen(symbol);
	while (*str != '\0')
	{
		if (*str == '"' || *str == '\'')
		{
			if (quote == 0)
				quote = *str;
			else if (quote == *str)
				quote = 0;
		}
		if (
			*str == *symbol
			&& ft_strncmp(str, symbol, sym_len) == 0
			&& quote == 0
		)
			return ((char *)str);
		str++;
	}
	return (NULL);
}
