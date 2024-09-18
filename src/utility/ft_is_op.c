/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:28:18 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/16 18:34:36 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Function to check if the current input character is an operator
 */
int	ft_is_op(char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '>' || *str == '<')
		return (1);
	if (*str == '(' || *str == ')')
		return (1);
	if (*str == '&' || *str == '|')
		return (1);
	return (0);
}
