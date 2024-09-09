/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_struct_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:38:24 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/18 15:18:46 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_printf_init(t_printf *s)
{
	s->write_count = 0;
	s->index = 0;
	s->size = 100;
	s->err = 0;
	s->str = (char *) malloc(s->size);
	if (!s->str)
		s->err = 1;
}

static void	*ft_realloc(void *src, size_t old_str, size_t new_str)
{
	size_t	i;
	void	*dst;
	char	*c_dst;
	char	*c_src;

	dst = (void *) malloc(old_str + new_str);
	if (!dst)
	{
		free (src);
		return (0);
	}
	c_dst = (char *) dst;
	c_src = (char *) src;
	i = 0;
	while (i < old_str)
	{
		c_dst[i] = c_src[i];
		i++;
	}
	free(src);
	return (dst);
}

void	ft_printf_realloc(t_printf *s)
{
	if (s->index >= s->size)
	{
		s->str = ft_realloc(s->str, s->size, s->size_added_str);
		if (!s->str)
			s->err = 1;
		s->size += s->size_added_str;
	}
}
