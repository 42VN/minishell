/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:22:42 by jazevedo          #+#    #+#             */
/*   Updated: 2024/11/26 22:45:19 by hitran           ###   ########.fr       */
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

char	*join_and_free(char *s1, char *s2)
{
	char	*res;
	char	*ptr;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	// len = len1 + len2;
	res = (char *)malloc(len1 + len2 + 2);
	if (!res)
		return (NULL);
	ptr = res;
	while (s1 && *s1)
		*res++ = *s1++;
	while (s2 && *s2)
		*res++ = *s2++;
	*res++ = '\n';
	*res = '\0';
	return (ptr);
}
