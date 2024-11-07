/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:37:26 by hitran            #+#    #+#             */
/*   Updated: 2024/11/07 20:58:17 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	make_root(t_ast *ast, t_token *tokens, int size, int index)
{
	t_token	*left;
	t_token	*right;
	int		close_index;

	if (!ast || !tokens || index == -1)
		return (0);
	left = extract_tokens(tokens, 0, index);
	right = extract_tokens(tokens, index + 1, size);
	ast->token = tokens[index];
	ast->left = build_ast(left);
	ast->right = build_ast(right);
	if (left)
		free_token (&left);
	if (right)
		free_token (&right);
	return (1);
}

int	inside_parenthesis(t_token *tokens, int index)
{
	int	depth;

	if (tokens[0].type != BR_OPEN || tokens[index -1].type != BR_CLOSE)
		return (0);
	depth = 0;
	while (--index >= 0)
	{
		if (tokens[index].type == BR_OPEN)
			depth++;
		else if (tokens[index].type == BR_CLOSE)
			depth--;
		if (depth == 0 && index != 0)
			return (0);
	}
	return (1);
}

t_ast	*build_ast(t_token *tokens)
{
	t_ast	*ast;
	int		size;
	t_token	*temp;

	if (!tokens)
		return (NULL);
	size = get_tokens_size(tokens);
	if (!size)
		return (NULL);
	if (inside_parenthesis(tokens, size))
	{
		temp = extract_tokens(tokens, 1, size - 1);
		ast = build_ast(temp);
		if (temp)
			free_token (&temp);
		return (ast);
	}
	ast = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (make_root(ast, tokens, size, locate_operator(tokens, size, 0)))
		return (ast);
	else if (make_root(ast, tokens, size, locate_operator(tokens, size, 1)))
		return (ast);
	if (tokens[0].type == CMD)
		ast->token = tokens[0];
	return (ast);
}
