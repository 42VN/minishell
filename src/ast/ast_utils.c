/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:37:26 by hitran            #+#    #+#             */
/*   Updated: 2024/12/16 14:14:02 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token **tokens)
{
	if (!tokens || !*tokens)
		return ;
	free(*tokens);
	*tokens = NULL;
}

int	locate_operator(t_token *tokens, int size, int priority)
{
	int	depth;
	int	index;

	depth = 0;
	index = -1;
	while (++index < size)
	{
		if (tokens[index].type == BR_OPEN)
			depth++;
		else if (tokens[index].type == BR_CLOSE)
			depth--;
		if (depth == 0 && priority == 0 && tokens[index].type == AND)
			return (index);
		else if (depth == 0 && priority == 1 && tokens[index].type == OR)
			return (index);
		else if (depth == 0 && priority == 2 && tokens[index].type == PIPE)
			return (index);
	}
	return (-1);
}

int	get_tokens_size(t_token *tokens)
{
	int	index;

	index = 0;
	if (!tokens)
		return (0);
	while (tokens[index].type || tokens[index].cmd)
		index++;
	return (index);
}

t_token	*extract_tokens(t_token *tokens, int start, int end)
{
	t_token	*res;
	int		index;

	if (end - start <= 0)
		return (NULL);
	res = (t_token *)ft_calloc(end - start + 1, sizeof(t_token));
	if (!res)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: memory allocation failed!\n");
		return (NULL);
	}
	index = 0;
	while (start < end)
		res[index++] = tokens[start++];
	ft_memset(&res[index], 0, sizeof(t_token));
	return (res);
}

void	ast_cleanup(t_ast **ast)
{
	if (!ast || !*ast)
		return ;
	if ((*ast)->left)
		ast_cleanup(&((*ast)->left));
	if ((*ast)->right)
		ast_cleanup(&((*ast)->right));
	free(*ast);
	*ast = NULL;
}
