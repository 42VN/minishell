/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:46:08 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/20 08:42:24 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

typedef struct s_shell	t_shell;

/**
 * Data structure for AST (Abstract Syntax Tree)
 */
typedef struct s_ast
{
	t_token			token;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

//---------------------------------|| WILDCARD||------------------------------//
int	wildcard(t_shell *shell, t_token *tokens, int size);

//---------------------------------||  UTILS  ||------------------------------//


#endif