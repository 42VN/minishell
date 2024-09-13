/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:37:26 by hitran            #+#    #+#             */
/*   Updated: 2024/09/13 22:16:25 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	get_tokens_size(t_token *tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return (0);
	while (tokens[i].str)
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
	{
		res[index].type = tokens[start].type;
		res[index].str = ft_strdup(tokens[start].str);
		start++;
		index++;
	}
	// printf("index = %d\n", index);
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
	ast->type = tokens[index].type;
	ast->arg = ft_strdup(tokens[index].str);
	ast->left = build_ast(left);
	ast->right = build_ast(right);
	return (1);
}

t_ast	*build_ast(t_token *tokens)
{
	t_ast	*ast;
	int		size;

	size = get_tokens_size(tokens);
	if (!size)
		return (NULL);
	// printf("size = %d\n", size);
	ast = (t_ast *)ft_calloc(1, sizeof(t_ast));
	// printf("locate logic = %d\n", locate_logic(tokens, size));
	if (make_root(ast, tokens, size, locate_logic(tokens, size)))
		return (ast);
	// printf("locate pipe = %d\n", locate_pipe(tokens, size));
	if (make_root(ast, tokens, size, locate_pipe(tokens, size)))
		return (ast);
	// printf("locate redirect = %d\n", locate_redirect(tokens, size));
	if (make_root(ast, tokens, size, locate_redirect(tokens, size)))
		return (ast);
	ast->type = tokens[size - 1].type;
	ast->arg = ft_strdup(tokens[size - 1].str);
	// printf("done\n");
	return (ast);
}
