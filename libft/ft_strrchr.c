/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:31:12 by ktieu             #+#    #+#             */
/*   Updated: 2024/04/18 12:56:18 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;

	tmp = 0;
	while (*s)
	{
		if (*s == (char) c)
		{
			tmp = (char *) s;
		}
		s++;
	}
	if (*s == (char) c)
	{
		return ((char *)s);
	}
	return ((char *)tmp);
}
