/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:27:38 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/05 17:21:15 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# if BUFFER_SIZE > 125000 || BUFFER_SIZE < 1
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 420
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

/*-----------------------------------------------------------------------*/
/*							HELPER FUNCTIONS                                */
/*-----------------------------------------------------------------------*/

char	*ft_strjoin_gnl(char *s1, char *s2, int *eol_index);
void	ft_strlcpy_gnl(char *dst, const char *src, size_t dst_size);

/*-----------------------------------------------------------------------*/
/*							MAIN FUNCTIONS									*/
/*-----------------------------------------------------------------------*/
char	*get_next_line(int fd);
char	*get_next_line_bonus(int fd);

#endif