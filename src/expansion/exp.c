/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:35:10 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/15 23:46:41 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_exp(
	char **cmd_arg,
	char **res,
	int is_exp)
{
	if (is_exp)
	{
		ft_free_null(cmd_arg);
		*cmd_arg = *res;
	}
	else
		free(*res);
}


static int	exp_get_str(t_shell *shell, int i, int j)
{
	char	*res;
	int		is_exp;

	is_exp = 1;
	res = ft_strdup("");
	if (!res)
		return (ft_error_ret("expansion: malloc", shell, ERR_MALLOC, 0));
	if (*shell->tokens->array[i].split_cmd[j] == '$')
		exp_dollar(shell, &res, shell->tokens->array[i].split_cmd[j]);
	else
		is_exp = 0;
	if (!res)
		return (ft_error_ret("expansion: malloc", shell, ERR_MALLOC, 0));
	replace_exp(&shell->tokens->array[i].split_cmd[j], &res, is_exp);
	return (1);
}

void	expansion(t_shell *shell)
{
	size_t	i;
	size_t	j;
	
	if (!shell || shell->err_type != ERR_NONE)
		return ;
	i = 0;
	j = 0;
	while (i <= shell->tokens->cur_pos)
	{
		while (shell->tokens->array[i].split_cmd[j])
		{
			exp_get_str(shell, i, j);
			++j;
		}
		++i;
	}
}
