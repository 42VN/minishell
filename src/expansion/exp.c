/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:35:10 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/29 17:51:09 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expansion_redirect(t_shell *shell, size_t i)
{
	t_redirect	*redirect;

	redirect = NULL;
	if (shell->tokens->array[i].redirect)
	{
		redirect = shell->tokens->array[i].redirect;
		while(redirect)
		{
			if (redirect->type == HEREDOC)
			{
				exp_remove_quotes(&redirect->path, 0);
				redirect = redirect->next;
				continue;
			}
			if (redirect->path)
			{
				if (!exp_logic(shell, &redirect->path))
					return (0);
			}
			redirect = redirect->next;
		}
	}
	return (1);
}

static int	expansion_cmd(t_shell *shell, size_t i)
{
	size_t	j;

	j = 0;
	if (shell->tokens->array[i].split_cmd)
	{
		j = 0;
		while (shell->tokens->array[i].split_cmd[j])
		{
			if (!exp_logic(shell, &shell->tokens->array[i].split_cmd[j]))
				return (0);
			++j;
		}
	}
	return (1);
}

int	expansion(t_shell *shell)
{
	size_t	i;
	
	if (!shell || shell->err_type != ERR_NONE)
		return (0);
	i = 0;
	while (i <= shell->tokens->cur_pos)
	{
		if (!expansion_redirect(shell, i))
			return (0);
		if (!expansion_cmd(shell, i))
			return (0);
		++i;
	}
	return (1);
}
