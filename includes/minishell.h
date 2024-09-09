/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:47:49 by hitran            #+#    #+#             */
/*   Updated: 2024/09/09 15:33:38 by hitran           ###   ########.fr       */
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
	COMMAND,				// command (ls, cat ...)
	ARGUMENT,				// option (-l, -d ...) or file (infile.txt)
	PIPE,					// |
	OR,						// ||
	AND,					// &&
	SEMI_COLON,				// ; (mkdir new; cd new; echo "successful")
	BACKGROUND,				// & (sleep 10 & echo "running another function")
	IN_REDIRECT,			// <
	OUT_REDIRECT,			// >
	APPEND_IN_REDIRECT,		// <<
	APPEND_OUT_REDIRECT,	// >>
	ERR_REDIRECT,			// 2> Error Redirection 
	COMBINED_REDIRECT		// &> Combined Output Redirection
}	t_token_type;

// typedef struct s_envp
// {
// 	char	**array;
// 	char	*path;
// 	int		level;
// }	t_envp;

typedef struct s_token
{
	int		type;
	char	*token;
}	t_token;

typedef struct s_msh
{
	char	*cwd;
	char	**envp;
	t_token	*tokens;
}	t_msh;

//---------------------------------||  PARSE  ||------------------------------//
void	parse_input(t_msh *msh);

//---------------------------------||  SIGNAL ||------------------------------//
void	wait_signal(int i);

//---------------------------------||  UTILS  ||------------------------------//
// void	get_envp(t_msh *msh, char **envp);
void	exit_error(t_msh *msh, char *str, int n);

#endif