/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:37:26 by hitran            #+#    #+#             */
/*   Updated: 2024/11/08 09:43:24 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function that frees an array of tokens
 * Description:
 * - Safely frees the memory allocated for the token array
 * - Sets the token pointer to NULL to avoid dangling references
 * Parameters:
 * - <tokens>: pointer to the token array to free
 */
void	free_token(t_token **tokens)
{
	if (!tokens || !*tokens)
		return ;
	free(*tokens);
	*tokens = NULL;
}

/**
 * Function that locates an operator in a token array
 * Description:
 * - Searches for the highest-priority operator at a certain depth
 * - Priority 0 targets logical operators (AND, OR)
 * - Priority 1 targets the PIPE operator
 * Parameters:
 * - <tokens>: array of tokens to search
 * - <index>: index to start searching from
 * - <priority>: priority of operator to find (0 for AND/OR, 1 for PIPE)
 * Returns:
 * - Index of the located operator
 * - -1 if no matching operator is found
 */
int	locate_operator(t_token *tokens, int index, int priority)
{
	int	depth;

	depth = 0;
	while (--index >= 0)
	{
		if (tokens[index].type == BR_OPEN)
			depth++;
		else if (tokens[index].type == BR_CLOSE)
			depth--;
		if (depth == 0 && priority == 0
			&& (tokens[index].type == AND || tokens[index].type == OR))
			return (index);
		else if (depth == 0 && priority == 1 && tokens[index].type == PIPE)
			return (index);
	}
	return (-1);
}

/**
 * Function that gets the size of a token array
 * Description:
 * - Counts the number of tokens until the end of the array
 * Parameters:
 * - <tokens>: array of tokens to measure
 * Returns:
 * - Number of tokens in the array
 * - 0 if the token array is NULL
 */
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

/**
 * Function that extracts a range of tokens from an array
 * Description:
 * - Allocates memory for a new token array in the specified range
 * - Sets a NULL token at the end of the array for safety
 * Parameters:
 * - <tokens>: source array of tokens to extract from
 * - <start>: starting index of the range
 * - <end>: ending index of the range (exclusive)
 * Returns:
 * - Pointer to a new token array containing the specified range
 * - NULL if the range is invalid or empty
 */
t_token	*extract_tokens(t_token *tokens, int start, int end)
{
	t_token	*res;
	int		index;

	if (end - start <= 0)
		return (NULL);
	res = (t_token *)ft_calloc(end - start + 1, sizeof(t_token));
	index = 0;
	while (start < end)
		res[index++] = tokens[start++];
	ft_memset(&res[index], 0, sizeof(t_token));
	return (res);
}

/**
 * Function that cleans up an Abstract Syntax Tree (AST)
 * Description:
 * - Recursively frees the AST, clearing left and right nodes
 * - Sets the AST pointer to NULL to avoid dangling references
 * Parameters:
 * - <ast>: double pointer to the root AST node to clean up
 */
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
