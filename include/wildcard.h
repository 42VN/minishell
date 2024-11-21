/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:46:08 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/21 15:36:42 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

#include "dirent.h"

typedef struct s_shell	t_shell;

//---------------------------------|| WILDCARD||------------------------------//
void	wildcard(t_shell *shell, t_token *tokens, int size);

//---------------------------------||  UTILS  ||------------------------------//
void	free_array(char **array);
int	array_length(char **array);
int	match_loop(const char **f, const char **p, const char **star,
	const char **match);
int	is_match(const char *file, const char *pattern);

#endif