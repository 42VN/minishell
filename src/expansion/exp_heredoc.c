/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:06:31 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/05 22:08:03 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exp_logic_hd(t_shell *shell, char **str)
{
	char	*res;

	res = ft_strdup("");
	if (!res)
		return (ft_error_ret("expansion: exp_logic: ft_strdup", shell, ERR_MALLOC, 0));
	exp_process(shell, &res, *str);
	if (!res)
		return (ft_error_ret("expansion: exp_logic: malloc", shell, ERR_MALLOC, 0));
	// exp_remove_quotes(&res, 0);
	ft_free_null(str);
	*str = res;
	return (1);
}

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
				if (redirect->no_exp == 0)
				{
					if (!exp_logic_hd(shell, &redirect->path))
						return (0);
				}
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
