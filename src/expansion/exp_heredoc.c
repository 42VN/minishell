/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:06:31 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/04 13:22:20 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expansion_redirect_heredoc(t_shell *shell, size_t i)
{
	t_redirect	*redirect;

	redirect = NULL;
	if (shell->tokens->array[i].redirect)
	{
		redirect = shell->tokens->array[i].redirect;
		while(redirect)
		{
			if (redirect->type == HEREDOC && redirect->path)
			{
				if (!exp_logic_str(shell, &redirect->path))
					return (0);
			}
			redirect = redirect->next;
		}
	}
	return (1);
}

int	expansion_heredoc(t_shell *shell)
{
	size_t	i;
	
	if (!shell || shell->err_type != ERR_NONE)
		return (0);
	i = 0;
	
	while (i <= shell->tokens->cur_pos)
	{
		if (!expansion_redirect_heredoc(shell, i))
			return (0);
		++i;
	}
	return (1);
}
