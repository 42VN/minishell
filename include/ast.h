/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:46:08 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/19 22:43:55 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef struct s_shell	t_shell;

/**
 * Data structure for AST (Abstract Syntax Tree)
 */
typedef struct s_ast
{
	t_token			token;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

//---------------------------------||   AST   ||------------------------------//
// int		read_heredoc(t_shell *shell, t_token *tokens, int size);
t_ast	*build_ast(t_token *tokens);

//---------------------------------||  UTILS  ||------------------------------//
void	free_token(t_token **tokens);
int		locate_operator(t_token *tokens, int index, int priority);
int		get_tokens_size(t_token *tokens);
t_token	*extract_tokens(t_token *tokens, int start, int end);
void	ast_cleanup(t_ast **ast);

#endif