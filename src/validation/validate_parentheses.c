/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_parentheses.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:38:19 by mito              #+#    #+#             */
/*   Updated: 2024/06/28 17:27:41 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"
#include "libft.h"

static void	update_quote(char *quote, int value)
{
	if (value == '\'' || value == '"')
	{
		if (*quote == 0)
			*quote = value;
		else if (*quote == value)
			*quote = 0;
	}
}

/**
 * Remove a `()` pair which is outside of quote pair.
 */
int	validate_parentheses(char *str)
{
	int		depth;
	char	quote;

	depth = 0;
	quote = 0;
	while (*str != '\0')
	{
		update_quote(&quote, *str);
		if (*str == '(' && quote == 0)
			depth++;
		if (*str == ')' && quote == 0)
			depth--;
		if (depth < 0)
		{
			ft_fprintf(\
				2, "minishell: syntax error near expected token '%c'\n", *str \
			);
			return (2);
		}
		str++;
	}
	if (depth == 0)
		return (0);
	ft_fprintf(2, "minishell: syntax error near expected token '('\n");
	return (2);
}
