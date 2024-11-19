/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:08:06 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/19 22:22:52 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

typedef struct s_shell	t_shell;

//---------------------------------|| HEREDOC ||------------------------------//
int	read_heredoc(t_shell *shell, t_token *tokens, int size);

//---------------------------------||  UTILS  ||------------------------------//
void	print_warning(char *eof);
char	*join_and_free(char *s1, char *s2);

#endif