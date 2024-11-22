/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:49:03 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/28 01:39:37 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include "minishell.h"
#include "io.h"
#include "utils.h"
#include "constants.h"
#include "minishell_signal.h"

static int	reduce(char **result, const char *str, t_minishell *minishell)
{
	const char	*dollar;
	const char	*value;
	int			i;

	dollar = ft_strchr(str, '$');
	if (dollar == NULL)
	{
		if (ft_concat(result, 1, str) < 0)
			return (-1);
		return (0);
	}
	i = 1;
	while (
		dollar[i] != '\0' && !ft_isspace(dollar[i])
		&& dollar[i] != '"' && dollar[i] != '\''
	)
		i++;
	value = resolve_env(&dollar[1], i - 1, minishell);
	if (value != NULL)
	{
		if (ft_concat(result, 1, value) < 0)
			return (-1);
	}
	return (reduce(result, &dollar[i], minishell));
}

static int	heredoc_expand(char **str, t_minishell *minishell)
{
	const char	*dollar;
	char		*result;

	dollar = ft_strchr(*str, '$');
	if (dollar == NULL)
		return (0);
	result = ft_substr(*str, 0, dollar - (*str));
	if (result == NULL)
		return (-1);
	if (reduce(&result, dollar, minishell) < 0)
	{
		free(result);
		return (-1);
	}
	if (result != NULL)
	{
		free(*str);
		*str = result;
	}
	return (0);
}

static int	get_heredoc_content(
	char **content,
	t_io *io,
	t_minishell *minishell,
	t_bool should_expand
)
{
	char	*line;

	errno = 0;
	while (1)
	{
		line = ft_readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, io->token) == 0)
			return (free(line), 0);
		if (should_expand && heredoc_expand(&line, minishell) < 0)
			return (free(line), -1);
		if (ft_concat(content, 2, line, "\n") < 0)
			return (free(line), -1);
		free(line);
	}
	if (errno)
		return (-1);
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}

static int	handle_io(t_node *node, void *minishell, size_t index)
{
	t_io *const	io = (t_io *)node->data;
	char		*content;
	t_bool		should_expand;

	(void)index;
	if (io->redi_type != REDIR_HEREDOC)
		return (0);
	should_expand = true;
	if (ft_strchr(io->token, '\'') || ft_strchr(io->token, '"'))
		should_expand = false;
	ft_remove_quote_pair(io->token);
	content = ft_strdup("");
	if (content == NULL)
		return (-1);
	if (get_heredoc_content(&content, io, minishell, should_expand) < 0)
		return (free(content), -1);
	if (content == NULL && errno)
		return (-1);
	if (content != NULL)
	{
		free(io->token);
		io->token = content;
	}
	return (0);
}

int	heredoc(t_list *cmd_list, t_minishell *minishell)
{
	t_node	*node;
	t_list	*io_list;

	if (set_signal_handler(SIGINT, sigint_handler_heredoc) < 0)
		return (-1);
	node = cmd_list->head;
	while (node != NULL)
	{
		io_list = ((t_command *)node->data)->io_list;
		if (ft_list_for_each(io_list, minishell, handle_io) < 0)
			return (-1);
		node = node->next;
	}
	return (0);
}
