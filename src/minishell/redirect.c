/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 23:10:16 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/27 13:07:03 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "minishell.h"
#include "constants.h"
#include "utils.h"
#include "io.h"

static int	get_heredoc_fd(const char *token)
{
	int	fds[2];

	if (pipe(fds) < 0)
		return (perror("minishell: pipe"), -1);
	if (write(fds[1], token, ft_strlen(token)) < 0)
	{
		perror("minishell: write");
		close(fds[0]);
		close(fds[1]);
		return (-1);
	}
	if (close(fds[1]) < 0)
	{
		perror("minishell: close");
		close(fds[0]);
		return (-1);
	}
	return (fds[0]);
}

static int	redirect_pipe(int fds[], int pipe_r, int pipe_w)
{
	if (fds[0] >= 0)
	{
		if (dup2_close(fds[0], STDIN_FILENO) < 0)
			return (-1);
	}
	else if (pipe_r >= 0)
	{
		if (dup2(pipe_r, STDIN_FILENO) < 0)
			return (-1);
	}
	if (fds[1] >= 0)
	{
		if (dup2_close(fds[1], STDOUT_FILENO) < 0)
			return (-1);
	}
	else if (pipe_w >= 0)
	{
		if (dup2(pipe_w, STDOUT_FILENO) < 0)
			return (-1);
	}
	return (0);
}

static int	handle_redir(t_node *node, void *data, size_t i)
{
	const t_redir_type	type = ((t_io *)node->data)->redi_type;
	const char			*token = ((t_io *)node->data)->token;
	int *const			fds = (int *)data;

	(void)i;
	if ((type == REDIR_HEREDOC || type == REDIR_INPUT) && fds[0] != INT_MIN)
		close(fds[0]);
	if ((type == REDIR_OUTPUT || type == REDIR_APPEND) && fds[1] != INT_MIN)
		close(fds[1]);
	if (type == REDIR_HEREDOC)
		fds[0] = get_heredoc_fd(token);
	if (type == REDIR_INPUT)
		fds[0] = open(token, O_RDONLY);
	if (type == REDIR_OUTPUT)
		fds[1] = open(token, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (type == REDIR_APPEND)
		fds[1] = open(token, O_RDWR | O_CREAT | O_APPEND, 0644);
	if ((fds[0] == -1 || fds[1] == -1) && type != REDIR_HEREDOC)
		return (ft_fprintf(2, "minishell: %s: %s\n", token, \
			strerror(errno)), -1);
	return (0);
}

int	redirect(t_list *io_list, int pipe_r, int pipe_w)
{
	int	fds[2];
	int	status;

	fds[0] = INT_MIN;
	fds[1] = INT_MIN;
	if (ft_list_for_each(io_list, fds, handle_redir) < 0)
		return (-1);
	status = redirect_pipe(fds, pipe_r, pipe_w);
	if (pipe_r >= 0)
	{
		if (close(pipe_r) < 0)
			status = -1;
	}
	if (pipe_w >= 0)
	{
		if (close(pipe_w) < 0)
			status = -1;
	}
	return (status);
}
