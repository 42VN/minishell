/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:30:58 by ktieu             #+#    #+#             */
/*   Updated: 2024/04/17 15:55:49 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, char const *src, size_t dst_len)
{
	size_t	len;

	len = 0;
	while (*(src + len))
		len++;
	if (!dst_len)
		return (len);
	while (--dst_len && *src)
	{
		*dest++ = *src++;
	}
	*dest = '\0';
	return (len);
}
