/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:20:57 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/18 15:17:41 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_print_format(t_printf *s, char specifier, va_list ap)
{
	char	*upper_base;
	char	*lower_base;

	upper_base = "0123456789ABCDEF";
	lower_base = "0123456789abcdef";
	if (specifier == 'c')
		ft_print_char(s, va_arg(ap, int));
	else if (specifier == 's')
		ft_print_str(s, va_arg(ap, char *));
	else if (specifier == 'p')
		ft_print_ptr(s, va_arg(ap, unsigned long long));
	else if (specifier == 'u')
		ft_print_num_base(s, va_arg(ap, unsigned int), 10, lower_base);
	else if (specifier == 'd' || specifier == 'i')
		ft_print_num_base(s, va_arg(ap, int), 10, lower_base);
	else if (specifier == 'x')
		ft_print_num_base(s, va_arg(ap, unsigned int), 16, lower_base);
	else if (specifier == 'X')
		ft_print_num_base(s, va_arg(ap, unsigned int), 16, upper_base);
	else if (specifier == '%')
		ft_print_char(s, specifier);
	else
		s->err = 1;
}
