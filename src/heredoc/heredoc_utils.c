/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:22:42 by jazevedo          #+#    #+#             */
/*   Updated: 2024/11/27 15:06:35 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_warning(char *eof)
{
	char		*tmp;
	int			len;
	const char	*ms1;
	const char	*ms2;

	ms1 = "minishell: warning: here-document at line 1 delimited by "
		"end-of-file (wanted `";
	ms2 = "')\n";
	len = ft_strlen(ms1) + ft_strlen(eof) + ft_strlen(ms2) + 1;
	tmp = (char *)ft_calloc(len, 1);
	if (!tmp)
	{
		ft_putstr_fd("minishell: error: allocation failed", STDERR_FILENO);
		return ;
	}
	ft_strlcat(tmp, ms1, len);
	ft_strlcat(tmp, eof, len);
	ft_strlcat(tmp, ms2, len);
	ft_putstr_fd(tmp, STDERR_FILENO);
	if (tmp)
		free(tmp);
}

int join_and_free(char **s1, char *s2)
{
	char *res;
	char *ptr;
	int index;

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
