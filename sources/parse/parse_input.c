/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:01:17 by hitran            #+#    #+#             */
/*   Updated: 2024/09/09 13:50:15 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char	*read_input(t_msh *msh)
{
	char	*user_input;

	user_input = readline("minishell>");
	if (!user_input)
		exit_error(msh, "exit", g_errno);
	else
		add_history(user_input);
	return (user_input);
}

void	parse_input(t_msh *msh)
{
	// char	*user_input;

	// user_input = read_input(msh);
	if (read_input(msh))
		g_errno  = 1;
	// create_token(user_input);
}
