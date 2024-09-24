/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:07:54 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/22 19:20:16 by ktieu            ###   ########.fr       */
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
	NONE,
	CMD,					// command
	PIPE,					// |
	OR,						// ||				#bonus
	AND,					// &&				#bonus
	BR_OPEN,				// ( 				#bonus
	BR_CLOSE,				// ) 				#bonus
	INVALID
}	t_token_type; // bo RD

typedef enum e_redirect_type
{
	RD_IN,					// <
	RD_OUT,					// >
	RD_HEREDOC,				// <<
	RD_APPEND,				// >>
}	t_redirect_type;

typedef enum e_err_type
{
	ERR_MEMORY,
	ERR_FORK,
	ERR_PIPE
}	t_err_type;

//----------------------------------------------------
// TOKEN 
//-----------------------------------------------------

typedef	struct s_redirect
{
	int					fd;
	t_redirect_type 	type;
	char				*path;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_token
{
	t_token_type	type;
	char			*cmd;
	char			**split_cmd;
	t_redirect		*redirect;
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

/**
 * Data structure for AST (Abstract Syntax Tree)
 */
typedef struct s_ast
{
	t_token			token;
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
	t_ast		*ast;
}	t_shell;

#endif