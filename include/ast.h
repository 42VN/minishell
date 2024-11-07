/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:46:08 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/07 21:09:35 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include <sys/wait.h>
typedef struct s_shell	t_shell;
#include <errno.h>

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
int		read_heredoc(t_token *tokens, int size);
t_ast	*build_ast(t_token *tokens);
char	*type_string(t_token_type type);
void	print_ast(t_ast *ast);
char	*redirect_string(t_redirect_type type);
int		get_tokens_size(t_token *tokens);
void 	ast_cleanup(t_ast **ast);


void	free_token(t_token **tokens);
int		locate_operator(t_token *tokens, int index, int priority);
int		get_tokens_size(t_token *tokens);
t_token	*extract_tokens(t_token *tokens, int start, int end);
void	ast_cleanup(t_ast **ast);

//---------------------------------||EXECUTION||------------------------------//

void	execute_ast(t_shell *shell, t_ast *ast);
char	*find_command_path(char **envp, char *command);
void	execute_command(t_shell *shell, t_token token);

char	**split_command(char *command);
int		ft_is_all_white_spaces(char *s);
void	handle_cmd_error(char **command, char *message, int free_pt);
int		skip_quotes(char *str, int i);
int		skip_word(char *str, int i);
//---------------------------------||  UTILS  ||------------------------------//

// void	print_ast(t_ast *ast);
void	redirect_fd(int from_fd, int to_fd);
void	ft_free_triptr(char ***str);
void	create_pipe(int *pipe_id);
pid_t	init_child(t_shell *shell);
int		update_status(t_shell *shell, int new_status); //0111
void	free_all(t_shell *shell);

//---------------------------------||  ERROR  ||------------------------------//

void	open_error(t_shell *shell, char *path, int *fd);
void 	fork_error(t_shell *shell);
void 	exec_error(t_shell *shell, char **splitted_cmd, char *command_path);

#endif