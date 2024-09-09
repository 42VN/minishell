/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:06:46 by ktieu             #+#    #+#             */
/*   Updated: 2024/04/20 14:40:15 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned
int, char))
{
	size_t			len;
	unsigned int	index;
	char			*res;
	char			*res_ptr;

	if (!s)
		return (0);
	index = 0;
	len = ft_strlen(s);
	res = (char *) malloc (sizeof(char) * (len + 1));
	if (!res)
		return (0);
	res_ptr = res;
	while (*s)
	{
		*res_ptr = f(index, *s);
		index++;
		s++;
		res_ptr++;
	}
	*res_ptr = '\0';
	return (res);
}
