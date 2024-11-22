/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redirect_op.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:37:37 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/26 16:55:11 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "utils.h"

static char	*get_operator(const char *str)
{
	char	quote;

	quote = 0;
	while (*str != '\0')
	{
		if (*str == '"' || *str == '\'')
		{
			if (quote == 0)
				quote = *str;
			else if (quote == *str)
				quote = 0;
		}
		if ((*str == '<' || *str == '>') && quote == 0)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

/**
 * Return redirection operator `<` or `>` in the given string, skipping all
 * operators that are inside `'` or `"`.
*/
void	find_redirect_op(const char *str, char **start, char **end)
{
	*start = NULL;
	*end = NULL;
	*start = get_operator(str);
	if (*start == NULL)
		return ;
	*end = *start;
	while (**end != '\0' && (**end == **start || ft_isspace(**end)))
		(*end)++;
	if (**end == '\0')
		return ;
	while (**end != '\0' && ft_strchr(DELIMITER_STOP_CHARS, **end) == NULL)
	{
		if (**end == '\'' || **end == '"')
		{
			*end = ft_strchr(*end + 1, **end);
			if (*end == NULL)
				return ;
		}
		(*end)++;
	}
}
