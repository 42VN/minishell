/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 22:53:12 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/19 13:39:00 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Recusive function remove quotes
 */
int	exp_remove_quotes(char **res, int i)
{
	char	quote;
	int		last_quote;

	quote = '\0';
	last_quote = -1;
	if (!res || !(*res))
		return (0);
	while ((*res)[i])
	{
		if ((*res)[i] == '\'' || (*res)[i] == '\"')
		{
			quote = (*res)[i];
			last_quote = exp_strip_quotes(*res, quote, i);
			if (last_quote >= i && (*res)[last_quote] != '\0')
			{
				exp_remove_quotes(res, last_quote);
			}
			return (1);
		}
		++i;
	}
	return (1);
}

void	exp_split_cmd_remove_quotes(char **split_str, size_t str_len)
{
	size_t	i;

	i = 0;
	while (i < str_len)
	{
		exp_remove_quotes(&split_str[i], 0);
		++i;
	}
	return ;
}

char	*exp_split_cmd_join(char **split_str)
{
	char	*res;
	char	*joined;
	size_t	i;

	i = 0;
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (split_str[i])
	{
		if (!*res)
			joined = ft_strjoin(res, split_str[i]);
		else
			joined = ft_strjoin_space(res, split_str[i]);
		if (!joined)
		{
			free(res);
			return (NULL);
		}
		free(res);
		res = joined;
		++i;
	}
	return (res);
}
