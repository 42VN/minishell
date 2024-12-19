/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 22:53:12 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/19 11:41:56 by ktieu            ###   ########.fr       */
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
		joined = ft_strjoin(res, split_str[i]);
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

char **exp_split_cmd_realloc_wildcard(
	size_t cmd_len,
	size_t *str_len,
	char **split_str,
	char ***old_res
)
{
	size_t	new_len;
	size_t	i;
	char	**res;

	i = 0;
	new_len = 0;
	while (split_str[new_len])
		(new_len)++;
	if (new_len > *str_len)
	{
		*str_len = new_len;
		res = (char **)ft_calloc(cmd_len + new_len + 1, sizeof(char *));
		if (!res)
		{
			if (*old_res)
				free(*old_res);
			return (NULL);
		}
		exp_split_cmd_cpy(res, old_res, 0, cmd_len);
		if (*old_res)
			free(*old_res);
		return (res);
	}
	else
		return (*old_res);
}

void	exp_split_cmd_cpy(char **res, char ***src, size_t start, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		res[i + start] = (*src)[i];
		(*src)[i] = NULL;
		++i;
	}
}
