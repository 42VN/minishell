/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:22:42 by jazevedo          #+#    #+#             */
/*   Updated: 2024/11/26 22:35:04 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	here_doc(t_shell *shell, t_redirect *redirect,
	char *line, char *heredoc)
{
	heredoc = ft_strdup("");
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
		if (!line) //ctrl + D
		{
			print_warning(redirect->path);
			break ;
		}
		if (shell->exitcode - 128 == SIGINT)
		{
			free(redirect->path);
			redirect->path = ft_strdup("");
			return (0);
		}
		if (!ft_strcmp(redirect->path, line))
		{
			free(line);
			break ;
		}
		heredoc = join_and_free(heredoc, line);
	}
	free(redirect->path);
	redirect->path = heredoc;
	return (1);
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
			if (!here_doc(shell, redirect, line, NULL))
				return (0);
			start_signal(shell, PARENT);
		}
		redirect = redirect->next;
	}
	return (1);
}

int	read_heredoc(t_shell *shell, t_token *tokens, int size)
{
	int	index;

	index = 0;
	while (index < size)
	{
		if (tokens[index].type == CMD)
		{
			if (!start_heredoc(shell, tokens[index].redirect))
				return (0);
		}
		index++;
	}
	return (1);
}
