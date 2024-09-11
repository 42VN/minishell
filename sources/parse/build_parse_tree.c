/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_parse_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 09:46:48 by hitran            #+#    #+#             */
/*   Updated: 2024/09/11 13:44:46 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	is_redirect(t_type type)
// {
// 	if (type == IN_REDIRECT || type == OUT_REDIRECT
// 		|| type == APPEND || type == HERE_DOC)
// 		return (1);
// 	return (0);
// }

int	need_transfer(t_token *right)
{
	if (right->first && right->first->next)
		return (1);
	return (0);
}

int	locate_(t_token **tokens, int size)
{
	t_node	*tmp;

	tmp = last;
	while (tmp)
	{
		if (tmp->type == AND || tmp->type == OR)
			return (tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}

t_node	*is_pipe(t_token **tokens, int size)
{
	t_node	*tmp;

	tmp = last;
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}

t_node	*is_redirect(t_token **tokens, int size)
{
	t_node	*tmp;

	tmp = last;
	while (tmp)
	{
		if (tmp->type == INPUT || tmp->type == OUTPUT \
		|| tmp->type == APPEND || tmp->type == HEREDOC)
			return (tmp);
		tmp = tmp->prev;
	}
	return (NULL);
}

t_token	*get_right(t_token *tokens, t_node *node)
{
	t_node		*tmp;
	t_token	*right;

	if (!tokens || !node)
		return (NULL);
	right = start_token();
	tmp = tokens->first;
	while (tmp && tmp != node)
		tmp = tmp->next;
	while (tmp)
	{
		add_token(right, tmp->type, ft_strdup(tmp->cmd));
		tmp = tmp->next;
	}
	return (right);
}

t_token	*get_left(t_token *tokens, t_node *node)
{
	t_node		*tmp;
	t_token	*left;

	if (!tokens || !node)
		return (NULL);
	left = start_token();
	tmp = tokens->first;
	while (tmp && tmp != node)
	{
		add_token(left, tmp->type, ft_strdup(tmp->cmd));
		tmp = tmp->next;
	}
	free_tokens2(tokens);
	return (left);
}

t_token	*remove_last(t_token *right)
{
	t_node		*tmp;
	t_token	*new_right;

	if (!right)
		return (NULL);
	new_right = start_token();
	tmp = right->first->next;
	while (tmp)
	{
		add_token(new_right, tmp->type, ft_strdup(tmp->cmd));
		tmp = tmp->next;
	}
	free_tokens2(right);
	return (new_right);
}

t_token	*get_from_right(t_token *left, t_token *right)
{
	t_node		*tmp;
	t_token	*new_left;

	if (!left || !right)
		return (NULL);
	new_left = start_token();
	tmp = left->first;
	while (tmp)
	{
		add_token(new_left, tmp->type, ft_strdup(tmp->cmd));
		tmp = tmp->next;
	}
	tmp = right->first->next;
	while (tmp)
	{
		add_token(new_left, tmp->type, ft_strdup(tmp->cmd));
		tmp = tmp->next;
	}
	free_tokens2(left);
	return (new_left);
}

t_token	*send_to_left(t_token *right)
{
	t_node		*tmp;
	t_token	*new_right;

	if (!right)
		return (NULL);
	new_right = start_token();
	tmp = right->first;
	add_token(new_right, tmp->type, ft_strdup(tmp->cmd));
	free_tokens2(right);
	return (new_right);
}

int	setup_root_nodes(t_tree *tree, t_token **tokens, int size)
{
	t_token	*left;
	t_token	*right;

	if (!tree || !tokens || !node)
		return (0);
	right = get_right(tokens, node);
	left = get_left(tokens, node);
	tree->type = right->first->type;
	right = remove_last(right);
	if (is_redir(tree->type) && need_transfer(right))
	{
		left = transfer_from_right(left, right);
		right = redirect_to_left(right);
	}
	tree->left = build_parse_tree(left);
	tree->right = build_parse_tree(right);
	return (1);
}

void	determine_execution_priority(t_tree *parse_tree, t_token **tokens)
{
	int		size;

	size = ft_matrixlen(tokens);
	if (setup_root_nodes(parse_tree, tokens, size))
		return ;
	if (tokens[size -1] && tokens[size -1]->type == PARENTHESIS)
		parse_tree->type = PARENTHESIS;
	else
		parse_tree->type = COMMAND;
	parse_tree->token = tokens;
}

t_tree	*build_parse_tree(t_token **tokens)
{
	t_tree	*parse_tree;

	parse_tree = (t_tree *)ft_calloc(sizeof(t_tree));
	if (!parse_tree)
		return (NULL);
	determine_execution_priority(parse_tree, tokens);
	return (parse_tree);
}
