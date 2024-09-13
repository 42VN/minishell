/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:07:02 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/13 12:23:28 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Function to check if the current input character is an operator
 */
int	ft_token_is_op(char *input)
{
	if (*input == '>' || *input == '<')
		return (1);
	if (*input == '|')
		return (1);
	if (*input == '(' || *input == ')')
		return (1);
	return (0);
}