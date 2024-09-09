/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:03:34 by ktieu             #+#    #+#             */
/*   Updated: 2024/04/18 10:51:32 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t src_len)
{
	unsigned char	*returned_dst;

	returned_dst = (unsigned char *) dst;
	if (dst == src)
		return (dst);
	if (dst < src)
	{
		while (src_len--)
		{
			*(char *)dst++ = *(char *)src++;
		}
	}
	else if (dst > src)
	{
		while (src_len--)
		{
			((char *)dst)[src_len] = ((char *)src)[src_len];
		}
	}
	return (returned_dst);
}
