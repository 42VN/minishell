/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 08:30:54 by hitran            #+#    #+#             */
/*   Updated: 2024/09/20 13:16:28 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_ast(t_shell *shell, t_ast *ast)
{
	if (ast->type == AND || ast->type == OR)
		execute_logic(shell, ast);
	else if (ast->type == PIPE)
		execute_pipe(shell, ast);
	else if (ast->left)
		execute_ast(shell, ast->left);
	else if (ast->right)
		execute_ast(shell, ast->right);
	else if (ast->arg)
		execute_command(shell, ast->token);
}
