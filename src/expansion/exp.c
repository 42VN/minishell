/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:35:10 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/05 14:58:46 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exp_getstr(t_shell *shell)
{
	size_t	i;
	size_t	j;
	char	*res;

	if (!shell || !shell->ast || shell->err_type != ERR_NONE)
		return ;
	i = 0;
	j = 0;
	res = ft_strdup("");
	while (res && shell->ast[i].token.cmd[j])
	{	
		if (shell->ast[i].token.cmd[j] == '$')
			exp_dollar(shell, res, shell->ast[i].token.cmd, &j);
	}
}



void	exp_ast(t_shell *shell)
{
	
}