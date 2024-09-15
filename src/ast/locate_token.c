/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:38:36 by hitran            #+#    #+#             */
/*   Updated: 2024/09/13 21:54:59 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	locate_logic(t_token *tokens, int index)
{
	while (--index >= 0)
	{
		if (tokens[index].type == AND || tokens[index].type == OR)
			return (index);
	}
	return (-1);
}

int	locate_pipe(t_token *tokens, int index)
{
	while (--index >= 0)
	{
		if (tokens[index].type == PIPE)
			return (index);
	}
	return (-1);
}

int	is_redirect(t_token_type type)
{
	return (type == RD_IN || type == RD_OUT
		|| type == RD_APPEND || type == RD_HEREDOC);
}

int	locate_redirect(t_token *tokens, int index)
{
	while (--index >= 0)
	{
		if (is_redirect(tokens[index].type))
			return (index);
	}
	return (-1);
}
