/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:29:53 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/24 10:22:24 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Extracts a string that forms part of a command from the input `ptr`.
 */
static char	*ft_get_str_cmd(char **ptr, t_shell *shell)
{
	char	*str;
	char	*start;
	size_t	len;

	len = 0;
	start = *ptr;
	while (**ptr && **ptr != ' ' && !ft_is_op(*ptr))
	{
		(*ptr)++;
		++len;
	}
	if (len == 0)
		return (NULL);
	str = ft_substr(start, 0, len);
	return (str);
}

/**
 * Handles the creation or update of command tokens. 
 * If there is no string in the token array at the current index, a new command is created.
 * Otherwise, the string is joined as an argument to the existing command.
 */
int	ft_token_handle_cmd(char **ptr, t_shell *shell)
{
	size_t			*index;
	char			*str;

	if (!ptr || !*ptr || !**ptr || !shell)
		return (0);
	index = &shell->tokens->cur_pos;
	if (!ft_is_op(*ptr))
	{
		str = ft_get_str_cmd(ptr, shell);
		if (!str)
			return (0);
		if (shell->tokens->array[*index].cmd == NULL)
		{
			shell->tokens->array[*index].type = CMD;
			shell->tokens->array[*index].cmd = str;
			shell->tokens->cur_pos++;
		}
		else
		{
			if (!ft_token_join_cmd(&shell->tokens->array[*index - 1], str))
				return (ft_free_null_ret(&str, 0));
		}
	}
	return (1);
}
