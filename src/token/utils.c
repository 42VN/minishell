/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:31:57 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/26 17:30:04 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	ft_token_type_is_op(t_token_type type)
{
	if (type == BR_OPEN || BR_CLOSE)
		return (1);
	else if (type == CMD)
		return (1);
	else if (type == PIPE || type == AND || type == OR)
		return (1);
	else
		return (0);
}

int	ft_token_check_closing_br(char *str)
{
	while (*str)
	{
		if (*str == ')')
			return (1);
		str++;
	}
	return (0);
}
