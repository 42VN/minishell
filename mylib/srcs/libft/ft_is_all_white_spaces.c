/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_all_white_spaces.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 22:52:19 by hitran            #+#    #+#             */
/*   Updated: 2024/08/03 22:52:38 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_all_white_spaces(char *s)
{
	while (*s)
	{
		if (*s != 32 && (*s < 9 || *s > 13))
			return (0);
		s++;
	}
	return (1);
}
