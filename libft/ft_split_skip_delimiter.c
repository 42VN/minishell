/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_skip_delimiter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:17:27 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/12 15:11:35 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_split_skip_delimiter(char const **s, char delimiter)
{
	while (**s && **s == delimiter)
		(*s)++;
}

const char	*ft_skip_quote(const char **s)
{
	char	quote;

	quote = **s;
	(*s)++;
	while (**s)
	{
		if (**s == quote)
		{
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
