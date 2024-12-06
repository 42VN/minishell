/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:04:21 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/06 16:34:19 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_shift_to_end(char **ptr)
{
	while (**ptr)
		(*ptr)++;
}

int	ft_space_count(char *command)
{
	int	count;
	int	in_word ;
	int	i;

	count = 0;
	in_word = 0;
	i = 0;
	if (!command)
		return (0);
	while (command[i] != '\0')
	{
		if (command[i] == ' ')
		{
			if (in_word)
				count++;
			in_word = 0;
		}
		else
			in_word = 1;
		++i;
	}
	return (count);
}
