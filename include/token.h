/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:47:30 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/28 23:48:14 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_shell	t_shell;

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
	NONE = 0,
	CMD = 1,
	PIPE = 2,
	OR = 3,
	AND = 4,
	BR_OPEN = 5,
	BR_CLOSE = 6,
}	t_token_type;

typedef enum e_redirect_type
{
	RD_IN,
	RD_OUT,
	RD_HEREDOC,
	RD_APPEND,
}	t_redirect_type;

typedef enum e_err_type
{
	ERR_NONE = 0,
	ERR_SYNTAX = 1,
	ERR_MALLOC = 2,
	ERR_FORK = 3,
	ERR_PIPE = 4
}	t_err_type;

typedef enum e_syntax_err
{
	ERR_SYNTAX_NONE = 0,
	ERR_SYNTAX_QUOTE = 1,
	ERR_SYNTAX_RD = 2,
	ERR_SYNTAX_LOGIC = 3,
	ERR_SYNTAX_BR = 4,
	ERR_SYNTAX_NORMAL = 5
}	t_syntax_err;

//----------------------------------------------------
// TOKEN 
//-----------------------------------------------------

typedef struct s_redirect
{
	int					fd;
	t_redirect_type		type;
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
	t_token				*array;
	size_t				size;
	size_t				cur_pos;
	size_t				to_add;
	int					br_open;
	t_syntax_err		syntax_err;
}	t_tokens;

//----------------------------------------------------
// PARSE 
//-----------------------------------------------------
char		*ft_quote_err(char *quote, t_shell *shell, char **ptr);
char		*ft_remove_quote(
				char *cmd,
				char quote,
				t_shell *shell,
				size_t len);
char		*ft_token_parse(char **ptr, t_shell *shell, int has_quote);

//----------------------------------------------------
// REDIRECT 
//-----------------------------------------------------
void		ft_redirect_append(t_redirect **head, t_redirect *new_redirect);
void		ft_redirect_clear(t_redirect **head);
t_redirect	*ft_token_redirect(t_shell *shell, char **str, char op, int count);

//----------------------------------------------------
// OPERATOR 
//-----------------------------------------------------
int			ft_token_handle_op(char **ptr, t_shell *shell);

//----------------------------------------------------
// CMD 
//-----------------------------------------------------

char		*ft_token_join_cmd(t_token *token, char **str);
int			ft_token_handle_cmd(char **ptr, t_shell *shell);
//----------------------------------------------------
// UTILS 
//-----------------------------------------------------
int			ft_token_realloc(t_shell *shell);
int			ft_token_is_last(char *str);
int			ft_check_op(t_shell *shell, char *str);
int			ft_redirect_check_path(char *str);
int			ft_token_increment_pos(t_shell *shell);
void		ft_token_free(t_shell *shell);
int			ft_syntax_err_ret(t_shell *shell, t_syntax_err err, int code);
int			ft_space_count(char *command);
//----------------------------------------------------
// CHECK 
//-----------------------------------------------------
int			ft_token_logic_precheck(t_shell *shell, char *str, size_t index);
int			ft_token_logic_postcheck(t_shell *shell, char *str);
int			ft_token_bracket_check(t_shell *shell, char *str, size_t index);
int			ft_token_redirect_precheck(t_shell *shell, char *str);
//----------------------------------------------------
// PRINT 
//-----------------------------------------------------
void		ft_token_print(t_shell *shell);
void		ft_redirect_print(t_redirect **head);
void		ft_token_syntax_err(t_shell *shell, char *ptr);
//----------------------------------------------------
// TOKEN 
//-----------------------------------------------------
int			tokenize(t_shell *shell, char *line);

#endif