/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:52:44 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/26 14:38:32 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_redirect	*ft_token_redirect(t_shell *shell, char **str, char op, int count)
{
	t_redirect	*redirect;
	char		*start;

	redirect = (t_redirect *)ft_calloc(1, sizeof(t_redirect));
	if (!redirect)
	{
		shell->err_type = ERR_MEMORY;
		return (NULL);
	}
	if (op == '<' && count == 1)
		redirect->type = RD_IN;
	else if (op == '>' && count == 1)
		redirect->type = RD_OUT;
	else if (op == '<' && count == 2)
		redirect->type = RD_HEREDOC;
	else if (op == '>' && count == 2)
		redirect->type = RD_APPEND;
	ft_skip_strchr(str, ' ');
	start = *str;
	while (**str && !ft_is_op(*str) && !ft_isspace(**str))
		(*str)++;
	redirect->path = ft_substr(start, 0, *str - start);
	return (redirect);
}

void	ft_redirect_append(t_redirect **head, t_redirect *new_redirect)
{
	t_redirect	*temp;

	if (!*head)
	{
		*head = new_redirect;
		return;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_redirect;
}

void	ft_redirect_clear(t_redirect **head)
{
	t_redirect	*temp;
	t_redirect	*next;

	if (!head || !*head)
		return;

	temp = *head;
	while (temp)
	{
		next = temp->next;
		if (temp->path)
			free(temp->path);
		free(temp);
		temp = next;
	}
	*head = NULL;
}
