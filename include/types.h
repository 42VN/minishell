/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:07:54 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/09 17:07:57 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_token_type
{
	CMD,					// command (ls, cat ...)
	ARG,					// option (-l, -d ...) or file (infile.txt)
	PIPE,					// |
	OR,						// ||
	AND,					// &&
	SEMICOLON,				// ; (mkdir new; cd new; echo "successful")
	BACKGROUND,				// & (sleep 10 & echo "running another function")
	REDIRECT_IN,			// <
	REDIRECT_OUT,			// >
	REDIRECT_ERR,			// 2> Error Redirection 
	REDIRECT_COMBINED,		// &> Combined Output Redirection
	HERE_DOC,				// <<
	APPEND					// >>
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*str;
}	t_token;

typedef struct s_shell
{
	char	**envp;
	char	*cwd;
	int		exited;
	int		aborted;
	t_token	*tokens;
}	t_shell;


typedef struct s_sighandler
{
	
}	t_sighandler;