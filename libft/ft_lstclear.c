/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:38:46 by ktieu             #+#    #+#             */
/*   Updated: 2024/04/22 15:58:03 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cur_node;
	t_list	*next_node;

	if (!lst || !del || !(*lst))
		return ;
	cur_node = (*lst);
	while (cur_node != NULL)
	{
		next_node = cur_node->next;
		del(cur_node->content);
		free(cur_node);
		cur_node = next_node;
	}
	*lst = NULL;
}
