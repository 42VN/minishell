/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:22:42 by jazevedo          #+#    #+#             */
/*   Updated: 2024/12/16 11:04:47 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	here_doc(t_shell *shell, t_redirect *redirect,
	char *line, char *heredoc)
{
	heredoc = ft_strdup("");
	if (!heredoc)
		return (EXIT_FAILURE);
	while (1)
	{
		//-------------------------------
		//Snippet for testing
		//-------------------------------
		if (isatty(fileno(stdin)))
			line = readline("> ");
		else
		{
			char *input;
			input = get_next_line(fileno(stdin));
			line = ft_strtrim(input, "\n");
			free(input);
		}
		if (!line)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: warning: here-document at "
				"line 1 delimited by end-of-file (wanted `%s')\n", redirect->path);
			break ;
		}
		if (shell->exitcode - 128 == SIGINT)
		{
			if (heredoc)
				free(heredoc);
			free(redirect->path);
			redirect->path = ft_strdup("");
			return (EXIT_FAILURE);
		}
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
			start_signal(shell, HEREDOC);
			if (here_doc(shell, redirect, line, NULL) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			start_signal(shell, PARENT);
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
