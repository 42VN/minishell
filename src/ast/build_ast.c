/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:37:26 by hitran            #+#    #+#             */
/*   Updated: 2024/09/20 09:56:20 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_tokens_size(t_token *tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return (0);
	while (tokens[i].type || tokens[i].cmd)
		i++;
	return (i);
}

static t_token	*extract_tokens(t_token *tokens, int start, int end)
{
	t_token	*res;
	int		index;

	if (end - start <= 0)
		return (NULL);
	res = (t_token *)ft_calloc(end - start + 1, sizeof(t_token));
	index = 0;
	while (start < end)
		res[index++] = tokens[start++];
	res[index] = (t_token){0};  //terminated-null
	return (res);
}

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
	return (1);
}

t_ast	*build_ast(t_token *tokens)
{
	t_ast	*ast;
	int		size;

	if (!tokens)
		return (NULL);
	size = get_tokens_size(tokens);
	if (!size)
		return (NULL);
	ast = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (make_root(ast, tokens, size, locate_logic(tokens, size)))
		return (ast);
	else if (make_root(ast, tokens, size, locate_pipe(tokens, size)))
		return (ast);
	ast->token = tokens[0];
	return (ast);
}
