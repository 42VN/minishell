/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_strchr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:00:06 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/08 11:48:33 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_skip_strchr(char **s, char delimiter)
{
	while (**s && **s == delimiter)
		(*s)++;
}

char	*ft_skip_quote(char **s)
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
