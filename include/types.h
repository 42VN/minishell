/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:07:54 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/10 21:29:54 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

//----------------------------------------------------
// ENUM
//-----------------------------------------------------

/**
 * Type of a token
 * 
 * Description:
 * -	[CMD]: command
 * -	[ARG]: command arguments/options
 * -	[PIPE, OR, AND, SEMICOLON]: operators
 * -	[RD]: redirect
 */
typedef enum e_token_type
{
	CMD,					// command (ls, cat ...)
	ARG,					// option (-l, -d ...) or file (infile.txt)
	PIPE,					// |
	OR,						// ||
	AND,					// &&
	SEMICOLON,				// ; (mkdir new; cd new; echo "successful")
	BACKGROUND,				// & (sleep 10 & echo "running another function")
	RD_IN,					// <
	RD_OUT,					// >
	RD_HEREDOC,				// <<
	RD_APPEND				// >>
}	t_token_type;

typedef enum e_err_type
{
	ERR_MEMORY,
	ERR_FORK,
}	t_err_type;

//----------------------------------------------------
// TOKEN 
//-----------------------------------------------------

typedef struct s_token
{
	t_token_type	type;
	char			*str;
}	t_token;

typedef struct s_tokens
{
	t_token	*array;
	size_t	size;
	size_t	cur_token;
	size_t	cur_pos;
	size_t	to_add;
}	t_tokens;

//----------------------------------------------------
// ABSTRACT SYNTAX TREE 
//-----------------------------------------------------

typedef enum e_ast_node_type
{
	AST_COMMAND,	// Represents a command node
	AST_OPERATOR,	// Represents an operator (e.g., pipe, OR, AND)
	AST_REDIRECT	// Represents a redirection (e.g., <, >, 2>)
} t_ast_node_type;

/**
 * Data structure for AST (Abstract Syntax Tree)
 */
typedef struct s_ast
{
	t_ast_node_type	type;
	t_token			*token;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

//----------------------------------------------------
// SHELL
//-----------------------------------------------------

typedef struct s_shell
{
	char		**envp;
	char		*cwd;
	int			aborted;
	int			exitcode;
	t_err_type	err_type;
	t_tokens	*tokens;
}	t_shell;


#endif