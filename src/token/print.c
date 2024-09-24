/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:15:55 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/24 11:48:01 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_redirect_print(t_redirect **head)
{
	t_redirect	*temp;
	char		*str;
	
	if (!*head)
		return;
	temp = *head;
	while (temp)
	{
		if (temp->type == RD_IN)
			str = "RD_IN";
		else if (temp->type == RD_OUT)
			str = "RD_OUT";
		else if (temp->type == RD_APPEND)
			str = "RD_APPEND";
		else if (temp->type == RD_HEREDOC)
			str = "RD_HEREDOC";
		printf("Path: %s, Type: %s\n", temp->path, str);
		temp = temp->next;
	}
}

void	ft_token_print(t_shell *shell)
{
	int				i;
	t_token_type	type;
	char			*type_str;

	i = 0;
	if (!shell->tokens)
		return ;
	while (i < shell->tokens->cur_pos)
	{
		type = shell->tokens->array[i].type;
		if (type == CMD)
			type_str = "CMD";
		else if (type == PIPE)
			type_str = "PIPE";
		else if (type == BR_OPEN)
			type_str = "BR_OPEN";
		else if (type == BR_CLOSE)
			type_str = "BR_CLOSE";
		else if (type == AND)
			type_str = "AND";
		else if (type == OR)
			type_str = "OR";
		else
			type_str = "UNKNOWN";
		printf("Token %d: [%s], Type: %s\n",
			i,
			shell->tokens->array[i].cmd, type_str);
		ft_redirect_print(&shell->tokens->array[i].redirect);
		++i;
	}
}



