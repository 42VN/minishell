/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:08:06 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/13 22:31:07 by hitran           ###   ########.fr       */
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
#include "./types.h"
#include "../src/token/token.h"

#define PROMPT "minishell> "

//----------------------------------------------------
// ENVP 
//-----------------------------------------------------

char	**envp_dup(char **envp);

//----------------------------------------------------
// SHELL 
//-----------------------------------------------------

int		shell_init(t_shell *shell, char **envp);
void	shell_cleanup(t_shell *shell);

//----------------------------------------------------
// PARSE 
//-----------------------------------------------------
t_ast	*build_ast(t_token *tokens);

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
int		locate_logic(t_token *tokens, int index);
int		locate_pipe(t_token *tokens, int index);
int		is_redirect(t_token_type type);
int		locate_redirect(t_token *tokens, int index);
int		get_tokens_size(t_token *tokens);
t_token	**convert2double(t_token *array);
void	print_ast(t_ast *ast);

#endif