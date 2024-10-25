/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:47:30 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/25 22:58:07 by ktieu            ###   ########.fr       */
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
	CMD = 1,					// command
	PIPE = 2,					// |
	OR = 3,						// ||				#bonus
	AND = 4,					// &&				#bonus
	BR_OPEN = 5,				// ( 				#bonus
	BR_CLOSE = 6,				// ) 				#bonus
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
	ERR_MALLOC,
	ERR_FORK,
	ERR_PIPE
}	t_err_type;

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
	t_token	*array;
	size_t	size;
	size_t	cur_pos;
	size_t	to_add;
	int		is_cmd;
	int		br_open;
}	t_tokens;

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
int			ft_token_check_op(t_shell *shell, char *str);
int			ft_token_check_closing_br(char *str);
int			ft_token_increment_pos(t_shell *shell);
void		ft_token_free(t_shell *shell);
//----------------------------------------------------
// PRINT 
//-----------------------------------------------------
void		ft_token_print(t_shell *shell);
void		ft_redirect_print(t_redirect **head);
void		ft_token_parse_error(char *ptr);
//----------------------------------------------------
// TOKEN 
//-----------------------------------------------------
int			tokenize(t_shell *shell, char *line);

#endif