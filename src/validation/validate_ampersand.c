/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_ampersand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:13:02 by mito              #+#    #+#             */
/*   Updated: 2024/06/21 16:23:43 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"
#include "constants.h"
#include "libft.h"
#include "utils.h"

static const char	*get_next(const char *str)
{
	if (*(str + 1) != *str)
		return (ft_fprintf(2, "%s `%s'\n", ERROR_SYNTAX, "&"), NULL);
	str = str + 2;
	while (*str != '\0' && ft_isspace(*str))
		str++;
	if (*str == '\0')
		return (ft_fprintf(2, "%s `%s'\n", ERROR_SYNTAX, "&&"), NULL);
	if (*str == '&')
		return (ft_fprintf(2, "%s `%s'\n", ERROR_SYNTAX, "&&"), NULL);
	while (*str != '\0' && !ft_isspace(*str))
		str++;
	return (str);
}

int	has_valid_ampersand(const char *str)
{
	const char	*symbol;
	const char	*next;

	if (ft_starts_with(str, "&&") == true)
	{
		ft_fprintf(2, "%s `%s'\n", ERROR_SYNTAX, "&&");
		return (2);
	}
	symbol = find_symbol(str, "&");
	if (symbol == NULL)
		return (0);
	next = get_next(symbol);
	if (next == NULL)
		return (2);
	return (has_valid_arrow(next));
}
