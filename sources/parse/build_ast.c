/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:37:26 by hitran            #+#    #+#             */
/*   Updated: 2024/09/13 11:43:11 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirect(t_token_type type)
{
	return (type == RD_IN || type == RD_OUT
			|| type == RD_APPEND || type == RD_HEREDOC);
}

int	locate_logic(t_token **tokens, int index)
{
	while (--index >= 0)
	{
		if (tokens[index]->type == AND || tokens[index]->type == OR)
			return (index);
	}
	return (-1);
}

int	locate_pipe(t_token **tokens, int index)
{
	while (--index >= 0)
	{
		if (tokens[index]->type == PIPE)
			return (index);
	}
	return (-1);
}

int	locate_redirect(t_token **tokens, int index)
{
	while (--index >= 0)
	{
		if (is_redirect(tokens[index]->type))
			return (index);
	}
	return (-1);
}

t_tokens	*extract_right(t_token **tokens, int size, int start)
{
	t_token **right;
	int		index;

	right = (t_token **)ft_calloc(size - index, sizeof(t_token *));
	index = 0;
	while (++start < size)
	{
		right[index]->type = tokens[start]->type;
		right[index]->str = ft_strdup(tokens[start]->str);
		index++;
	}
	return (right);
}

t_tokens	*extract_left(t_token **tokens, int end)
{
	t_token **left;
	int		index;

	left = (t_token **)ft_calloc(end, sizeof(t_token *));
	index = -1;
	while (++index < end)
	{
		left[index]->type = tokens[index]->type;
		left[index]->str = ft_strdup(tokens[index]->str);
		index++;
	}
	return (left);
}

int	make_root(t_ast *ast, t_token **tokens, int size, int index)
{
	t_token	**left;
	t_token	**right;

	if (!ast || !tokens || index != -1)
		return (0);
	right = extract_right(tokens, size, index);
	left = extract_left(tokens, index);
	ast->type = tokens[index]->type;
	ast->left = build_ast(left, ft_matrixlen(left));
	ast->right = build_ast(right, ft_matrixlen(right));
	return (1);
}

t_ast	*build_ast(t_token **tokens, int size)
{
	t_ast	*ast;
	int		index;

	ast = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (make_root(ast, tokens, size, locate_logic(tokens, size)))
		return (ast);
	if (make_root(ast, tokens, size, locate_pipe(tokens, size)))
		return (ast);
	if (make_root(ast, tokens, size, locate_redirect(tokens, size)))
		return (ast);
	ast->type = tokens[size - 1]->type;
	ast->arg = tokens[size - 1]->str;
	return (ast);
}
