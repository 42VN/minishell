/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:37:12 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/10 21:00:00 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcount(char const *s, char delimiter)
{
	int	count;

	count = 0;
	while (*s)
	{
		ft_skip_strchr(&s, delimiter);
		if (*s)
		{
			count++;
			while (*s && *s != delimiter)
				s++;
		}
	}
	return (count);
}

static void	ft_free_all(char **array, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**ft_split_helper(char **res, char const *s, char delimiter, size_t i)
{
	size_t	cur_word_len;
	char	*start;

	while (*s)
	{
		ft_skip_strchr(&s, delimiter);
		if (*s)
		{
			start = (char *) s;
			while (*s && *s != delimiter)
				s++;
			cur_word_len = s - start;
			res[i] = (char *)malloc((cur_word_len + 1) * sizeof(char));
			if (!res[i])
			{
				ft_free_all(res, i);
				return (NULL);
			}
			ft_memcpy(res[i], start, cur_word_len);
			res[i++][cur_word_len] = '\0';
		}
	}
	res[i] = NULL;
	return (res);
}

char	**ft_split(char const *s, char delimiter)
{
	char	**res;
	size_t	size;
	size_t	index;

	index = 0;
	size = ft_wordcount(s, delimiter);
	res = (char **)malloc((size + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	return (ft_split_helper(res, s, delimiter, index));
}
