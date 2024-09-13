/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:37:26 by hitran            #+#    #+#             */
/*   Updated: 2024/09/13 12:42:36 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_tokens_size(t_token **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return (0);
	while (tokens[i])
		i++;
	return (i);
}

static t_token	**extract_tokens(t_token **tokens, int start, int end)
{
	t_token	**right;
	int		index;

	if (end - start <= 0)
		return (NULL);
	right = (t_token **)ft_calloc(end - start + 1, sizeof(t_token *));
	index = 0;
	while (start < end)
	{
		right[index]->type = tokens[start]->type;
		right[index]->str = ft_strdup(tokens[start]->str);
		start++;
		index++;
	}
	return (right);
}

static int	make_root(t_ast *ast, t_token **tokens, int size, int index)
{
	t_token	**left;
	t_token	**right;

	if (!ast || !tokens || index != -1)
		return (0);
	left = extract_tokens(tokens, 0, index);
	right = extract_tokens(tokens, index + 1, size);
	ast->type = tokens[index]->type;
	ast->left = build_ast(left, get_tokens_size(left));
	ast->right = build_ast(right, get_tokens_size(right));
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
