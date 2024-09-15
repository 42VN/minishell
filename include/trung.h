/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trung.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:02:54 by hitran            #+#    #+#             */
/*   Updated: 2024/09/15 09:29:21 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRUNG_H
# define TRUNG_H

//---------------------------------||   AST   ||------------------------------//

t_ast	*build_ast(t_token *tokens);

//---------------------------------||EXECUTION||------------------------------//

void	execute_ast(t_shell *shell, t_ast *ast);
void	execute_logic(t_shell *shell, t_ast *ast);
int		update_status(int new_status);

//---------------------------------||  UTILS  ||------------------------------//

int		locate_logic(t_token *tokens, int index);
int		locate_pipe(t_token *tokens, int index);
int		is_redirect(t_token_type type);
int		locate_redirect(t_token *tokens, int index);
void	print_ast(t_ast *ast);

#endif