/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:22:34 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/08 19:50:46 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_check_value(t_shell *shell, char **value_str)
{
	
	if (!*value_str)
		return ;
	if (ft_isspace(**value_str) || !(**value_str))
		*value_str = NULL;
	if ((**value_str == '\'' || **value_str=='\"')
		&& (*(*value_str + 1) == '\'' || *(*value_str + 1)=='\"'))
	{
		*value_str = NULL;
	}
}