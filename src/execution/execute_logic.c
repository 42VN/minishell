/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 08:31:14 by hitran            #+#    #+#             */
/*   Updated: 2024/09/15 09:20:57 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_logic(t_shell *shell, t_ast *ast)
{
	if (ast->type == AND)
	{
		if (ast->left)
			execute_ast(shell, ast->left);
		if (update_status(-1) == 0 && ast->right)
			execute_ast(shell, ast->right);
	}
	else if (ast->type == OR)
	{
		if (ast->left)
			execute_ast(shell, ast->left);
		if (update_status(-1) != 0 && ast->right)
			execute_ast(shell, ast->right);
	}
}
