/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:49:36 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/20 16:52:31 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_redirect(char *str)
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

/**
 * Function to check and move the pointer of the string
*/
int	ft_is_redirect_move(char **str)
{
	if (!str || !**str)
		return (0);
	if (*str == '>' || *str == '<')
		return (1);
	return (0);
}
