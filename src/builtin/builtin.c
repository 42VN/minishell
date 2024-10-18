/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:04:40 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/18 15:08:38 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_builtin_type	get_builtin(char *str)
{
	if (ft_strcmp(str, "cd") == 0)
		return (BI_CD);
	else if (ft_strcmp(str, "pwd") == 0)
		return (BI_PWD);
	else if (ft_strcmp(str, "echo") == 0)
		return (BI_ECHO);
	else if (ft_strcmp(str, "exit") == 0)
		return (BI_EXIT);
	else if (ft_strcmp(str, "env") == 0)
		return (BI_ENV);
	else if (ft_strcmp(str, "export") == 0)
		return (BI_EXPORT);
	else if (ft_strcmp(str, "unset") == 0)
		return (BI_UNSET);
	return (BI_UNDEFINED);
}
