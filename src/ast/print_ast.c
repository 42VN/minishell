/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 22:18:06 by hitran            #+#    #+#             */
/*   Updated: 2024/09/24 14:58:26 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*type_string(t_token_type type)
{
	char *str;
	if (type == CMD)
		str= "CMD";
	else if (type == RD_IN)
		str= "RD_IN";
	else if (type == RD_OUT)
		str= "RD_OUT";
	else if (type == PIPE)
		str= "PIPE";
	else if (type == RD_APPEND)
		str= "RD_APPEND";
	else if (type == RD_HEREDOC)
		str= "RD_HEREDOC";
	else if (type == BR_OPEN)
		str= "BR_OPEN";
	else if (type == BR_CLOSE)
		str= "BR_CLOSE";
	else
		str = NULL;
	return (str);
}

void	print_ast(t_ast *ast)
{
	if (!ast)
		return ;
	printf("root = %s\n", type_string(ast->token.type));
	if (ast->left)
	{
		printf("left branch:\n");
		print_ast(ast->left);
	}
	if (ast->right)
	{
		printf("right branch:\n");
		print_ast(ast->right);
	}
	if(ast->token.cmd)
	printf("cmd = %s\n", ast->token.cmd);
}
