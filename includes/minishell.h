/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:47:49 by hitran            #+#    #+#             */
/*   Updated: 2024/09/11 14:48:06 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "mylib.h"
# include <stdio.h>						// printf
# include <readline/readline.h>			// readline
# include <readline/history.h>			// readline
# include <signal.h>   					// SIGINT, SIGQUIT, SIGTERM, sigaction

# define CWD_SIZE 4096
extern int g_errno;

typedef enum e_token_type
{
	CMD,					// command
	PIPE,					// |
	RD_IN,					// <
	RD_OUT,					// >
	RD_HEREDOC,				// <<
	RD_APPEND,				// >>
	OR,						// ||				#bonus
	AND,					// &&				#bonus
	BR_OPEN,				// ( 				#bonus
	BR_CLOSE				// ) 				#bonus
}	t_token_type;

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

/**
 * Data structure for AST (Abstract Syntax Tree)
 */
typedef struct s_ast
{
	t_token_type	type;
	t_token			*token;
	char			*path;
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
	// t_err_type	err_type;
	t_tokens	*tokens;
	t_ast		*ast;
}	t_shell;

//---------------------------------||  PARSE  ||------------------------------//
void	parse_input(t_shell *msh);

//---------------------------------||  SIGNAL ||------------------------------//
void	wait_signal(int i);

//---------------------------------||  UTILS  ||------------------------------//
// void	get_envp(t_shell *msh, char **envp);
void	exit_error(t_shell *msh, char *str, int n);

#endif