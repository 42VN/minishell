/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:35:35 by mito              #+#    #+#             */
/*   Updated: 2024/06/21 16:21:25 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

int	validate_input(char *str)
{
	int	status;

	status = validate_quotes_closed(str);
	if (status > 0)
		return (status);
	status = has_valid_arrow(str);
	if (status > 0)
		return (status);
	status = has_valid_vertical_bar(str);
	if (status > 0)
		return (status);
	status = has_valid_ampersand(str);
	if (status > 0)
		return (status);
	status = validate_parentheses(str);
	if (status > 0)
		return (status);
	return (0);
}
