/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trung.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:02:54 by hitran            #+#    #+#             */
/*   Updated: 2024/09/27 11:56:34 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRUNG_H
# define TRUNG_H

# include <sys/wait.h>
//---------------------------------||   AST   ||------------------------------//

t_ast	*build_ast(t_token *tokens);

//---------------------------------||EXECUTION||------------------------------//

void	execute_ast(t_shell *shell, t_ast *ast);
void	execute_logic(t_shell *shell, t_ast *ast);
int		update_status(int new_status);
void	execute_pipe(t_shell *shell, t_ast *ast);
char	*find_command_path(char **envp, char *command);
void	execute_command(t_shell *shell, t_token token);

//---------------------------------||  UTILS  ||------------------------------//

int		locate_logic(t_token *tokens, int index);
int		locate_pipe(t_token *tokens, int index);
int		is_redirect(t_token_type type);
int		locate_redirect(t_token *tokens, int index);
void	print_ast(t_ast *ast);
void	redirect_fd(int from_fd, int to_fd);
void	ft_free_triptr(char ***str);
void	create_pipe(int *pipe_id);

#endif