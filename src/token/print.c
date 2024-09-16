/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:15:55 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/16 11:01:32 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_token_print(t_shell *shell)
{
	int				i;
	t_token_type	type;
	char			*type_str;

	i = 0;
	while (i < shell->tokens->cur_pos)
	{
		type = shell->tokens->array[i].type;
		if (type == CMD)
			type_str = "CMD";
		else if (type == RD_IN)
			type_str = "RD_IN";
		else if (type == RD_OUT)
			type_str = "RD_OUT";
		else if (type == PIPE)
			type_str = "PIPE";
		else if (type == RD_APPEND)
			type_str = "RD_APPEND";
		else if (type == RD_HEREDOC)
			type_str = "RD_HEREDOC";
		else if (type == BR_OPEN)
			type_str = "BR_OPEN";
		else if (type == BR_CLOSE)
			type_str = "BR_CLOSE";
		else if (type == AND)
			type_str = "AND";
		else if (type == OR)
			type_str = "OR";
		printf("Token %d: [%s], Type: %s\n",
			i,
			shell->tokens->array[i].str, type_str);
		++i;
	}
}

