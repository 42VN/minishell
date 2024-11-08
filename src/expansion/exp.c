/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:35:10 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/08 15:51:49 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_exp(
	t_shell *shell,
	size_t i, 
	size_t j,
	char *exp_char)
{
	if (!exp_char)
		return ;
	ft_free_null(&shell->tokens->array[i].split_cmd[j]);
	shell->tokens->array[i].split_cmd[j] = exp_char;
	printf("I: %zu, J: %zu\n", i, j);
}


static int	exp_get_str(t_shell *shell, int i)
{
	size_t	j;

	char	*res;

	j = 0;
	res = ft_strdup("");
	while (res && shell->tokens->array[i].split_cmd[j])
	{
		if (*shell->tokens->array[i].split_cmd[j] == '$')
			exp_dollar(shell, &res, shell->tokens->array[i].split_cmd[j]);
		++j;
	}
	if (res)
		replace_exp(shell, i, j, res);
	else
		return (ft_error_ret("expansion: malloc", shell, ERR_MALLOC, 0));
	return (1);
}

void	expansion(t_shell *shell)
{

	size_t	i;
	
	i = 0;
	if (!shell || shell->err_type != ERR_NONE)
		return ;
	while (i <= shell->tokens->cur_pos)
	{
		exp_get_str(shell, i);
		++i;
	}
}