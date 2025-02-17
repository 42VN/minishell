/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:54:56 by hitran            #+#    #+#             */
/*   Updated: 2025/02/17 15:54:58 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	here_doc(t_shell *shell, t_redirect *redirect,
	char *line, char *heredoc)
{
	heredoc = ft_strdup("");
	if (!heredoc)
		return (EXIT_FAILURE);
	shell->exitcode = 0;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			print_warning(redirect->path);
			break ;
		}
		if (shell->exitcode - 128 == SIGINT)
			return (heredoc_sigint(heredoc, &redirect->path, line));
		if (!ft_strcmp(redirect->path, line))
		{
			free(line);
			break ;
		}
		if (join_and_free(&heredoc, line) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	free(redirect->path);
	redirect->path = heredoc;
	return (EXIT_SUCCESS);
}

static int	start_heredoc(t_shell *shell, t_redirect *redirect)
{
	char	*line;

	line = NULL;
	while (redirect)
	{
		if (redirect->type == RD_HEREDOC)
		{
			heredoc_signal(shell);
			if (here_doc(shell, redirect, line, NULL) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		redirect = redirect->next;
	}
	return (EXIT_SUCCESS);
}

int	read_heredoc(t_shell *shell, t_token *tokens, int size)
{
	int	index;

	index = 0;
	while (index < size)
	{
		if (tokens[index].type == CMD)
		{
			if (start_heredoc(shell, tokens[index].redirect) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		index++;
	}
	return (EXIT_SUCCESS);
}
