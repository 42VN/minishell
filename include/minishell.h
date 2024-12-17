/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:08:06 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/17 12:20:17 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>

# include "../libft/libft.h"
# include "token.h"
# include "heredoc.h"
# include "wildcard.h"
# include "ast.h"
# include "execution.h"
# include "builtin.h"
# include "environment.h"
# include "expansion.h"
# include "signals.h"

# define PROMPT "minishell> "

typedef struct s_shell
{
	char		**envp;
	char		*cwd;
	char		*old_pwd;
	int			aborted;
	int			exitcode;
	t_err_type	err_type;
	t_tokens	*tokens;
	t_ast		*ast;
	int			signal_flag;
}	t_shell;

//----------------------------------------------------
// SHELL 
//-----------------------------------------------------

int		shell_init(t_shell *shell, char **envp);
void	shell_cleanup(t_shell *shell);
void	minishell(t_shell *shell);

//----------------------------------------------------
// UTILS 
//-----------------------------------------------------

void	ft_exit(char *str, int exitcode);
int		ft_error_ret(
			char *str,
			t_shell *shell,
			t_err_type type,
			int return_code);
char	*ft_error_ret_null(
			char *str,
			t_shell *shell,
			t_err_type type);
char	*ft_prompt(char *prefix);
int		ft_is_op(char c);
int		ft_is_op_redirect(char c);
int		ft_is_op_logic(char c);
int		ft_is_op_bracket(char c);
char	*ft_strjoin_space(char const *s1, char const *s2);

char	**ft_split_quote(char *s, char delimiter);
void	free_array(char **array);
int		array_length(char **array);

#endif