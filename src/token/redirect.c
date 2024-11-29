/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:52:44 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/29 16:26:12 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirect_check_path(char *str)
{
	if (*str == '\0' || ft_is_op(*str))
		return (0);
	return (1);
}

void	ft_redirect_classify(t_redirect *redirect, char op, int count)
{
	if (!redirect)
		return ;
	if (op == '<' && count == 1)
		redirect->type = RD_IN;
	else if (op == '>' && count == 1)
		redirect->type = RD_OUT;
	else if (op == '<' && count == 2)
		redirect->type = RD_HEREDOC;
	else if (op == '>' && count == 2)
		redirect->type = RD_APPEND;
}

t_redirect	*ft_token_redirect(t_shell *shell, char **str, char op, int count)
{
	t_redirect	*redirect;
	char		*path;

	redirect = (t_redirect *)ft_calloc(1, sizeof(t_redirect));
	if (!redirect)
	{
		shell->err_type = ERR_MALLOC;
		return (NULL);
	}
	ft_redirect_classify(redirect, op, count);
	ft_skip_strchr(str, ' ');
	if (**str == '\0')
	{
		free(redirect);
		return (NULL);
	}
	path = ft_token_parse(str, shell, 0);
	if (!path && shell->err_type == ERR_MALLOC)
	{
		free(redirect);
		return (NULL);
	}
	redirect->path = path;
	return (redirect);
}

void	ft_redirect_append(t_redirect **head, t_redirect *new_redirect)
{
	t_redirect	*temp;

	if (!*head)
	{
		*head = new_redirect;
		return ;
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
		return ;
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
