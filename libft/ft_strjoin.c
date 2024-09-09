/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:37:15 by ktieu             #+#    #+#             */
/*   Updated: 2024/04/19 14:03:11 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	char	*ptr_res;

	if (!s1 || !s2)
		return (0);
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (0);
	ptr_res = res;
	while (*s1 != '\0')
	{
		*ptr_res++ = *s1++;
	}
	while (*s2 != '\0')
	{
		*ptr_res ++ = *s2++;
	}
	*ptr_res = '\0';
	return (res);
}
