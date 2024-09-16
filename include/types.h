/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:07:54 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/16 15:32:54 by hitran           ###   ########.fr       */
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
	CMD,					// command
	PIPE,					// |
	OR,						// ||				#bonus
	AND,					// &&				#bonus
	BR_OPEN,				// ( 				#bonus
	BR_CLOSE				// ) 				#bonus
}	t_token_type; // bo RD

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
	t_token_type	type; // CMD, PIPE, AND, OR, BR_OPEN/CLOSE bo RD
	char			**command; // sua thanh ** chua command va option + redirect (neu co)
	//neu co redirect, chuyen no thanh command[0] voi dinh dang la RD viet lien voi path
	// vi du: < "__path" grep hello  -> command[0] = <__path (_ la space); command[1] = grep; command[2] = hello
	// khi execute: kiem tra command[0][0] == < || > || << || >> -> open(&command[0][1]) ->tang pointer command ->command[1]
	// neu k co RD, giu nguyen
	// goi exeve(command[0], command)
}	t_token;

typedef struct s_tokens
{
	t_token	*array;
	size_t	size;
	size_t	cur_token;
	size_t	cur_pos;
	size_t	to_add;
	int		need_join;
}	t_tokens;

//----------------------------------------------------
// ABSTRACT SYNTAX TREE 
//-----------------------------------------------------

/**
 * Data structure for AST (Abstract Syntax Tree)
 */
typedef struct s_ast
{
	t_token_type	type;
	char			*arg;
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