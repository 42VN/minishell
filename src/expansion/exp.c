/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:35:10 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/11 13:53:10 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expansion_redirect(t_shell *shell, size_t i)
{
	t_redirect	*redirect;

	if (shell->tokens->array[i].redirect)
	{
		redirect = shell->tokens->array[i].redirect;
		while (redirect)
		{
			if (redirect->type == HEREDOC && redirect->path)
			{
				if (ft_strchr(redirect->path, '\'')
					|| ft_strchr(redirect->path, '\"'))
					redirect->no_exp = 1;
				exp_remove_quotes(&redirect->path, 0);
				redirect = redirect->next;
				continue ;
			}
			if (redirect->path)
			{
				if (!exp_logic_str(shell, &redirect->path))
					return (0);
			}
			redirect = redirect->next;
		}
	}
	return (1);
}

/**
 * Expansion for cmd and cmd args
 * 
 * Description:
 * 
 * -	Create and add new post-expansion string
 * to new split cmd array (2d array)
 */
static int	expansion_cmd(t_shell *shell, size_t i)
{
	size_t	j;
	size_t	len;
	char	**new_split_cmd;

	j = 0;
	len = 0;
	if (shell->tokens->array[i].split_cmd)
	{
		while (shell->tokens->array[i].split_cmd[len])
			len++;
		new_split_cmd = (char **)ft_calloc(1, (len + 1) * sizeof(char *));
		if (!new_split_cmd)
			return (ft_error_ret("expansion: expansion_cmd: ft_calloc",
					shell, ERR_MALLOC, 0));
		while (shell->tokens->array[i].split_cmd[j])
		{
			if (!exp_logic_split_str(shell,
					&shell->tokens->array[i].split_cmd[j], &new_split_cmd))
				return (0);
			++j;
		}
		ft_multi_free_null(&shell->tokens->array[i].split_cmd);
		shell->tokens->array[i].split_cmd = new_split_cmd;
	}
	return (1);
}

int	expansion(t_shell *shell)
{
	size_t	i;

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
