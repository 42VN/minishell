/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:06:05 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/18 15:18:40 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_print_address(t_printf *s, unsigned long num)
{
	if (num >= 16)
	{
		ft_print_address(s, num / 16);
		ft_print_address(s, num % 16);
	}
	else
	{
		if (num < 10)
			ft_print_char(s, num + '0');
		else
			ft_print_char(s, 'a' + (num - 10));
	}
}

void	ft_print_ptr(t_printf *s, unsigned long long ptr)
{
	ft_print_char(s, '0');
	ft_print_char(s, 'x');
	if (!ptr)
	{
		ft_print_char(s, '0');
	}
	else
	{
		ft_print_address(s, ptr);
	}
}
