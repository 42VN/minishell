/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:22:42 by jazevedo          #+#    #+#             */
/*   Updated: 2024/11/19 22:54:56 by hitran           ###   ########.fr       */
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
	int		len;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len = len1 + len2;
	res = (char *)malloc(len + 2);
	if (!res)
		return (NULL);
	if (s1)
	{
		ft_memcpy(res, s1, len1);
		free (s1);
	}
	if (s2)
	{
		ft_memcpy(res, s2, len2);
		free (s2);
	}
	res[len1 + len2] = '\n';
	res[len1 + len2 + 1] = '\0';
	return (res);
}
