/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:46:00 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/20 11:51:27 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

/**
 * Count the number of words in a string, including quoted words.
 */
size_t	ft_wordcount_delimiter(char *s, char delimiter)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		ft_skip_strchr((char **)&s, delimiter);
		if (*s)
		{
			count++;
			if (*s == '\'' || *s == '\"')
			{
				if (ft_skip_quote(&s) == NULL)
					break ;
			}
			else
			{
				while (*s && *s != delimiter && *s != '\'' && *s != '\"')
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
			(*s) += 2; // Skip escaped characters
		else if (**s == quote)
		{
			*s += 1; // Include the closing quote
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
	char delimiter,
	size_t *current_word_len)
{
	*start = *s;
	*current_word_len = 0;
	if (**s == '\'' || **s == '\"')
	{
		ft_cal_word_quote(s, start, current_word_len, **s);
	}
	else
	{
		while (**s && **s != delimiter)
			(*s)++;
		*current_word_len = *s - *start;
	}
}

/**
 * Helper function to allocate and split the string into words.
 */
static char	**ft_split_helper(
	char **res,
	char *s,
	char delimiter,
	size_t i
)
{
	size_t		current_word_len;
	char		*start;

	while (*s)
	{
		ft_skip_strchr((char **)&s, delimiter);
		if (*s)
		{
			ft_cal_word_alloc(&s, &start, delimiter, &current_word_len);
			res[i] = (char *)malloc((current_word_len + 1) * sizeof(char));
			if (!res[i])
			{
				ft_multi_free_null(&res);
				return (NULL);
			}
			ft_memcpy(res[i], start, current_word_len);
			res[i][current_word_len] = '\0';
			i++;
		}
	}
	res[i] = NULL;
	return (res);
}

/**
 * Split a string by a delimiter, preserving quotes.
 */
char	**ft_split_quote(char *s, char delimiter)
{
	char	**res;
	size_t	size;

	size = ft_wordcount_delimiter(s, delimiter);
	res = (char **)malloc((size + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	return (ft_split_helper(res, s, delimiter, 0));
}
