/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:27:42 by hitran            #+#    #+#             */
/*   Updated: 2024/12/19 11:18:35 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes_array(char **split_cmd)
{
	int	index;

	index = 0;
	while (split_cmd[index])
	{
		exp_remove_quotes(&split_cmd[index], 0);
		index++;
	}
}

int	remove_quotes(t_token *tokens, int size)
{
	int	index;

	index = 0;
	while (index < size)
	{
		if (tokens[index].type == CMD && tokens[index].split_cmd)
			remove_quotes_array(tokens[index].split_cmd);
		index++;
	}
	return (EXIT_SUCCESS);
}
