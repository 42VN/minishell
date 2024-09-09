/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:01:03 by ktieu             #+#    #+#             */
/*   Updated: 2024/04/18 16:04:18 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*res;
	char	*tmp;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	tmp = (char *) s;
	res = (char *) malloc (sizeof(char) * len + 1);
	if (!res)
		return (0);
	while (tmp[i])
	{
		res[i] = tmp[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
