/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote_wc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:41:58 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/11 14:58:09 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Count the number of words in a string, including quoted words.
 */
size_t	ft_wordcount_wc(char *s)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (ft_isspace(*s))
			ft_skip_strchr((char **)&s, *s);
		if (*s)
		{
			count++;
			while (*s && !ft_isspace(*s))
			{
				if (*s == '\'' && *s == '\"')
					ft_skip_quote(&s);
				else
					s++;
			}
		}
	}
	return (count);
}

/**
 * Calculate the length of a quoted word, including the enclosing quotes.
 */
static void	ft_cal_word_quote(
	char **s,
	char **start,
	size_t *current_word_len,
	char quote
)
{
	*start = *s;
	(*s)++;
	while (**s)
	{
		if (**s == '\\' && *(*s + 1))
			(*s) += 2;
		else if (**s == quote)
		{
			*s += 1;
			*current_word_len = *s - *start;
			return ;
		}
		else
			(*s)++;
	}
}

/**
 * Calculate the length of a word, handling quoted and unquoted cases.
 */
static void	ft_cal_word_alloc(
	char **s,
	char **start,
	size_t *current_word_len)
{
	char	*quote_start;
	size_t	quoted_len;

	*start = *s;
	*current_word_len = 0;
	while (**s && !ft_isspace(**s))
	{
		if (**s == '\'' || **s == '\"')
		{
			quote_start = *s;
			quoted_len = 0;
			ft_cal_word_quote(s, &quote_start, &quoted_len, **s);
			*current_word_len += quoted_len;
		}
		else
			(*s)++;
	}
	*current_word_len = *s - *start;
}

/**
 * Helper function to allocate and split the string into words.
 */
static char	**ft_split_helper(
	char **res,
	char *s,
	size_t i
)
{
	size_t		current_word_len;
	char		*start;

	while (*s)
	{
		while (ft_isspace(*s))
			ft_skip_strchr((char **)&s, *s);
		if (*s)
		{
			ft_cal_word_alloc(&s, &start, &current_word_len);
			res[i] = (char *)ft_calloc(current_word_len + 1, sizeof(char));
			if (!res[i])
			{
				ft_multi_free_null(&res);
				return (NULL);
			}
			ft_memcpy(res[i], start, current_word_len);
			i++;
		}
	}
	res[i] = NULL;
	return (res);
}

/**
 * Split a string by a delimiter, preserving quotes.
 */
char	**ft_split_quote_wc(char *s)
{
	char	**res;
	size_t	size;

	size = ft_wordcount_wc(s);
	res = (char **)malloc((size + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	return (ft_split_helper(res, s, 0));
}
