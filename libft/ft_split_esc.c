/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_esc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:30:27 by ktieu             #+#    #+#             */
/*   Updated: 2024/07/16 11:21:37 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wordcount_delimiter(const char *s, char delimiter)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		ft_split_skip_delimiter(&s, delimiter);
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

static void	ft_cal_word_quote(
	const char **s,
	const char **start,
	size_t *current_word_len,
	char quote
)
{
	int	esc_count;

	esc_count = 0;
	if (**s == '\'' || **s == '\"')
	{
		(*s)++;
		*start = *s;
		while (**s)
		{
			if (**s == '\\' && *(*s + 1))
			{
				esc_count++;
				(*s) += 2;
			}
			else if (**s == quote)
			{
				*current_word_len = *s - *start - esc_count;
				(*s)++;
				return ;
			}
			else
				(*s)++;
		}
	}
}

static void	ft_cal_word_alloc(
	const char **s,
	const char **start,
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

static char	**ft_split_helper(
	char **res,
	const char *s,
	char delimiter,
	size_t i
)
{
	size_t		current_word_len;
	const char	*start;

	while (*s)
	{
		ft_split_skip_delimiter(&s, delimiter);
		if (*s)
		{
			ft_cal_word_alloc(&s, &start, delimiter, &current_word_len);
			res[i] = (char *)malloc((current_word_len + 1) * sizeof(char));
			if (!res[i])
			{
				ft_multiple_free_set_null(&res);
				return (NULL);
			}
			ft_memcpy_esc(res[i], start, current_word_len);
			res[i][current_word_len] = '\0';
			i++;
		}
	}
	res[i] = NULL;
	return (res);
}

char	**ft_split_esc(const char *s, char delimiter)
{
	char	**res;
	size_t	size;

	size = ft_wordcount_delimiter(s, delimiter);
	res = (char **)malloc((size + 1) * sizeof(char *));
	if (!res)
	{
		return (NULL);
	}
	return (ft_split_helper(res, s, delimiter, 0));
}
