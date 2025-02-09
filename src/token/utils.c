/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:31:57 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/06 16:31:24 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function joins the current cmd in a token with a new one.
 */
char	*ft_token_join_cmd(t_token *token, char **str)
{
	char	*cmd;

	cmd = token->cmd;
	token->cmd = ft_strjoin_space(cmd, *str);
	free(cmd);
	ft_free_null(str);
	if (!token->cmd)
	{
		return (NULL);
	}
	return (token->cmd);
}

int	ft_token_is_last(char *str)
{
	while (*str && *str == ' ')
		str++;
	if (*str == '\0')
		return (1);
	return (0);
}

/**
 * Function that check and update the current status of the array of tokens
 * 
 * Descruption:
 * 
 * -	Check if there are 2 consecutive operators (AND, OR, PIPE)
 * 
 * -	Increment the current position in the array 
 * 		if the current string is a separator (AND, OR, PIPE, BRACKETS)
 */
int	ft_check_op(t_shell *shell, char *str)
{
	size_t			index;
	t_token_type	prev_type;

	index = shell->tokens->cur_pos;
	if (shell->tokens->array[index].type != NONE
		&& (ft_is_op_bracket(*str) || ft_is_op_logic(*str)))
	{
		if (!ft_token_increment_pos(shell))
			return (0);
	}
	index = shell->tokens->cur_pos;
	if (index > 0)
	{
		prev_type = shell->tokens->array[index - 1].type;
		if ((prev_type == PIPE || prev_type == AND || prev_type == OR)
			&& (*str == '|' || *str == '&'))
		{
			return (0);
		}
	}
	return (1);
}

/**
 * Function that safely update the current position of the array of tokens
 */
int	ft_token_increment_pos(t_shell *shell)
{
	size_t	new_pos;

	new_pos = shell->tokens->cur_pos + 1;
	if (!ft_token_realloc(shell))
		return (0);
	shell->tokens->cur_pos = new_pos;
	return (1);
}
