/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:16:13 by ktieu             #+#    #+#             */
/*   Updated: 2024/04/22 09:06:24 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long int	res;
	int				sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		if (res > 922337203685477580
			|| (res == 922337203685477580 && (sign * (*str - 48) > 7)))
			return (-1);
		if (res == 922337203685477580 && (sign * (*str - 48) < -8))
			return (0);
		res = res * 10 + (*str - 48);
		str++;
	}
	return (res * sign);
}
