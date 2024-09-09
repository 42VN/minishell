/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:01:16 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/18 15:18:29 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_print_num_base(t_printf *s, long long n, int base, char *lst_base)
{
	if (n < 0)
	{
		ft_print_char(s, (int) '-');
		ft_print_num_base(s, -n, base, lst_base);
		return ;
	}
	if (n >= base)
	{
		ft_print_num_base(s, n / base, base, lst_base);
		ft_print_num_base(s, n % base, base, lst_base);
		return ;
	}
	else
	{
		ft_print_char(s, lst_base[n]);
		return ;
	}
}
