/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:22:02 by mito              #+#    #+#             */
/*   Updated: 2024/05/30 15:13:57 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"
#include "libft.h"

static int	handle_error(char quote)
{
	if (
		ft_fprintf(
			STDERR_FILENO,
			"minishell: unexpected EOF while looking for matching `%c'\n",
			quote
		) < 0
	)
		return (1);
	if (
		ft_fprintf(
			STDERR_FILENO,
			"minishell: syntax error: unexpected end of file\n"
		) < 0
	)
		return (1);
	return (2);
}

int	validate_quotes_closed(char *str)
{
	char	quote;
	int		quote_count;
	int		i;

	quote_count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = str[i];
			while (str[i] != '\0' && quote_count < 2)
			{
				if (str[i] == quote)
					quote_count++;
				i++;
			}
			if (quote_count != 2)
				return (handle_error(quote));
			quote_count = 0;
		}
		else
			i++;
	}
	return (0);
}
