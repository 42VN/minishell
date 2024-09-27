/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:29:53 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/28 00:50:57 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_get_string_quote(char **ptr, char **start, t_shell *shell)
{
	size_t	len;
	char	*str;

	(*start)++;
	ft_skip_quote((const char **)ptr);
	if (!(*ptr))
		return (NULL);
	len = *ptr - *start - 1;
	if (len == 0)
		return (NULL);
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!str)
	{
		shell->err_type = ERR_MALLOC;
		return (NULL);
	}
	ft_memcpy_esc(str, *start, len);
	str[len] = '\0';
	return (str);
}

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
	if (*start == '\'' || *start == '\"')
	{
		return (ft_get_string_quote(ptr, &start, shell));
	}
	else
	{
		while (**ptr && **ptr != ' ' && !ft_is_op(**ptr))
		{
			(*ptr)++;
			len++;
		}
		if (len == 0)
			return (NULL);
		str = ft_substr(start, 0, len);
		return (str);
	}
}

/**
 * - Handles the creation or update of command tokens. 
 * - If there is no string in the token array
 * at the current index, a new command is created.
 * - Otherwise, the string is joined as an argument to the existing command.
 */
int	ft_token_handle_cmd(char **ptr, t_shell *shell)
{
	size_t			*index;
	char			*str;

	if (!**ptr)
		return (1);
	index = &shell->tokens->cur_pos;
	if (!ft_is_op(**ptr))
	{
		str = ft_get_str_cmd(ptr, shell);
		if (!str)
			return (0);
		if (shell->tokens->is_cmd == 1)
		{
			shell->tokens->array[*index].type = CMD;
			shell->tokens->array[*index].cmd = str;
			shell->tokens->is_cmd = 0;
		}
		else if (index > 0)
		{
			if (!ft_token_join_cmd(&shell->tokens->array[*index], &str))
				return (ft_free_null_ret(&str, 0));
		}
	}
	return (1);
}
