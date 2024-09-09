/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:12:19 by ktieu             #+#    #+#             */
/*   Updated: 2024/04/17 17:32:46 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t		dst_len;
	size_t		total_len;

	if ((!dst || !src) && !n)
		return (0);
	dst_len = 0;
	while (*(dst + dst_len) && dst_len < n)
		dst_len++;
	if (dst_len < n)
		total_len = dst_len + ft_strlen(src);
	else
		return (n + ft_strlen(src));
	while (*src && (dst_len + 1) < n)
	{
		*(dst + dst_len) = *src++;
		dst_len++;
	}
	*(dst + dst_len) = '\0';
	return (total_len);
}
