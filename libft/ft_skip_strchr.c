/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_strchr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:00:06 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/13 14:56:08 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_skip_strchr(char const **s, char delimiter)
{
	while (**s && **s == delimiter)
		(*s)++;
}

const char	*ft_skip_quote(const char **s, int has_quote)
{
	char	quote;

	quote = **s;
	if (has_quote == 0)
		(*s)++;
	while (**s)
	{
		if (**s == quote)
		{
			if (has_quote == 0)
				(*s)++;
			return (*s);
		}
		else if (**s == '\\' && *(*s + 1))
		{
			(*s) += 2;
		}
		else
			(*s)++;
	}
	return (NULL);
}

void	*ft_memcpy_esc(void	*dst, void const *src, size_t n)
{
	void	*return_dst;

	return_dst = dst;
	if (!dst && !src)
		return (dst);
	while (n--)
	{
		if (*(char *)src == '\\')
			src++;
		*(char *)dst++ = *(char *)src++;
	}
	return (return_dst);
}
