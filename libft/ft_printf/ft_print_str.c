/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:58:25 by ktieu             #+#    #+#             */
/*   Updated: 2024/06/18 15:11:14 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_print_str(t_printf *s, char *str)
{
	if (!str)
		return (ft_print_str(s, "(null)"));
	while (*str)
	{
		ft_print_char(s, *str);
		str++;
	}
}
