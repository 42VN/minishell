/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:08:06 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/18 09:28:49 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "../libft/libft.h"
#include "builtin.h"
#include "token.h"
#include "ast.h"

#define PROMPT "minishell> "

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

//----------------------------------------------------
// ENVP 
//-----------------------------------------------------

char	*env_get(char **envp, char *key, int include_key);
char	**env_dup(char **envp);
void	env_print(char **envp);
int		env_set(t_shell *shell, char *key, char *value);
void 	env_unset(t_shell *shell, char *key);

//----------------------------------------------------
// SHELL 
//-----------------------------------------------------

int		shell_init(t_shell *shell, char **envp);
void	shell_cleanup(t_shell *shell);

//----------------------------------------------------
// UTILS 
//-----------------------------------------------------

void 	ft_exit(char *str, int exitcode);
int		ft_error_ret(
			char *str,
			t_shell *shell,
			t_err_type type,
			int return_code);
char	*ft_prompt(char *prefix);
int		ft_is_op(char c);
int		ft_is_op_redirect(char c);
int		ft_is_op_logic(char c);
int		ft_is_op_bracket(char c);
char	*ft_strjoin_space(char const *s1, char const *s2);

#endif