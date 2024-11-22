/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_vertical_bar.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:47:09 by mito              #+#    #+#             */
/*   Updated: 2024/06/21 16:24:02 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"
#include "constants.h"
#include "libft.h"
#include "utils.h"

static const char	*get_next(const char *str, int count)
{
	if (*(str + 1) == *str)
	{
		count++;
		str++;
	}
	str++;
	while (*str != '\0' && ft_isspace(*str))
		str++;
	if (*str == '\0')
	{
		if (count == 1)
			return (ft_fprintf(2, "%s `%s'\n", ERROR_SYNTAX, "|"), NULL);
		else
			return (ft_fprintf(2, "%s `%s'\n", ERROR_SYNTAX, "||"), NULL);
	}
	if (*str == '|')
	{
		if (*(str + 1) != '|')
			return (ft_fprintf(2, "%s `%s'\n", ERROR_SYNTAX, "|"), NULL);
		return (ft_fprintf(2, "%s `%s'\n", ERROR_SYNTAX, "||"), NULL);
	}
	while (*str != '\0' && !ft_isspace(*str))
		str++;
	return (str);
}

int	has_valid_vertical_bar(const char *str)
{
	const char	*symbol;
	const char	*next;

	if (ft_starts_with(str, "||") == true)
		return (ft_fprintf(2, "%s `%s'\n", ERROR_SYNTAX, "||"), 2);
	if (ft_starts_with(str, "|") == true)
		return (ft_fprintf(2, "%s `%s'\n", ERROR_SYNTAX, "|"), 2);
	symbol = find_symbol(str, "|");
	if (symbol == NULL)
		return (0);
	next = get_next(symbol, 1);
	if (next == NULL)
		return (2);
	return (has_valid_vertical_bar(next));
}
