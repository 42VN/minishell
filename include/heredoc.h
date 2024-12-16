/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:08:06 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/16 11:14:27 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

typedef struct s_shell	t_shell;

//---------------------------------|| HEREDOC ||------------------------------//
int		read_heredoc(t_shell *shell, t_token *tokens, int size);

//---------------------------------||  UTILS  ||------------------------------//
int		join_and_free(char **s1, char *s2);
void	print_warning(char *path);
int		heredoc_sigint(char *heredoc, char **path);

#endif