/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:09:49 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/30 16:12:37 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include "../../include/minishell.h"

char	*ft_find_op_quote(char *cmd)
{
	int		i;
	char	*op_quote;
	
	i = 0;
	op_quote = NULL;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			op_quote = cmd + i;
			break;
		}
		i++;
	}
	return (op_quote);
}