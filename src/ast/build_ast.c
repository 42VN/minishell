/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:37:26 by hitran            #+#    #+#             */
/*   Updated: 2024/12/16 14:29:10 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	make_root(t_ast *ast, t_token *tokens, int size, int index)
{
	t_token	*left;
	t_token	*right;

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

static int	inside_parenthesis(t_token *tokens, int size)
{
	int	depth;
	int	index;

	if (size < 2 || tokens[0].type != BR_OPEN
		|| tokens[size - 1].type != BR_CLOSE)
		return (0);
	depth = 0;
	index = -1;
	while (++index < size)
	{
		if (tokens[index].type == BR_OPEN)
			depth++;
		else if (tokens[index].type == BR_CLOSE)
		{
			depth--;
			if (depth < 0)
				return (0);
		}
		else if (depth == 0 && index != 0)
			return (0);
	}
	return (depth == 0);
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
		if (!temp)
			return (NULL);
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
	else if (make_root(ast, tokens, size, locate_operator(tokens, size, 2)))
		return (ast);
	if (tokens[0].type == CMD)
		ast->token = tokens[0];
	return (ast);
}
