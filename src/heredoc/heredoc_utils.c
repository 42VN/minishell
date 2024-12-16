/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:22:42 by jazevedo          #+#    #+#             */
/*   Updated: 2024/12/16 09:57:49 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	join_and_free(char **s1, char *s2)
{
	char	*res;
	char	*ptr;
	int		index;

	res = (char *)malloc(ft_strlen(*s1) + ft_strlen(s2) + 2);
	if (!res)
		return (EXIT_FAILURE);
	ptr = res;
	index = 0;
	while (*s1 && (*s1)[index])
		*ptr++ = (*s1)[index++];
	index = 0;
	while (s2 && s2[index])
		*ptr++ = s2[index++];
	*ptr++ = '\n';
	*ptr = '\0';
	if (*s1)
		free(*s1);
	if (s2)
		free(s2);
	*s1 = res;
	return (EXIT_SUCCESS);
}
