/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:22:42 by jazevedo          #+#    #+#             */
/*   Updated: 2024/11/15 11:35:46 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_warning(char *eof)
{
	char		*tmp;
	int			len;
	const char	*ms1;
	const char	*ms2;

	ms1 = "minishell: warning: here-document at line 1 delimited by "
			"end-of-file (wanted `";
	ms2 = "')\n";
	len = ft_strlen(ms1) + ft_strlen(eof) + ft_strlen(ms2) + 1;
	tmp = (char *)ft_calloc(len, 1);
	if (!tmp)
	{
		ft_putstr_fd("minishell: error: allocation failed", STDERR_FILENO);
		return ;
	}
	ft_strlcat(tmp, ms1, len);
	ft_strlcat(tmp, eof, len);
	ft_strlcat(tmp, ms2, len);
	ft_putstr_fd(tmp, STDERR_FILENO);
	if (tmp)
		free(tmp);
}

/**
 * Function that joins two strings and frees them
 * Description:
 * - Concatenates <s1> and <s2> into a new string
 * - Frees <s1> and <s2> if they are not NULL
 * - Adds a newline character at the end of the result
 * Parameters:
 * - <s1>: first string to join
 * - <s2>: second string to join
 * Returns:
 * - New string with <s1>, <s2>, and a newline, or NULL on allocation failure
 */
static char	*join_and_free(char *s1, char *s2)
{
	char	*res;
	int		len;
	int		len1;
	int		len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len = len1 + len2;
	res = (char *)malloc(len + 2);
	if (!res)
		return (NULL);
	if (s1)
	{
		ft_memcpy(res, s1, len1);
		free (s1);
	}
	if (s2)
	{
		ft_memcpy(res, s2, len2);
		free (s2);
	}
	res[len1 + len2] = '\n';
	res[len1 + len2 + 1] = '\0';
	return (res);
}

/**
 * Function that reads input for a here-document and stores it in redirect->path
 * Description:
 * - Continuously reads input lines until the path is entered as the delimiter
 * - Joins each line with heredoc content using <join_and_free>
 * Parameters:
 * - <redirect>: pointer to the redirect struct storing heredoc data
 * Returns:
 * - 1 if heredoc is successfully read and stored
 * - 0 if an error occurs or allocation fails
 */
static int	here_doc(t_shell *shell, t_redirect *redirect)
{
	char	*line;
	char	*heredoc;

	heredoc = NULL;
	set_signals(shell, HEREDOC);
	while (1)
	{
		line = readline("> ");
		if (!line)
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
	// if (!heredoc)
	// 	return (0);
	free(redirect->path);
	redirect->path = heredoc;
	set_signals(shell, PARENT);
	return (1);
}

/**
 * Function that starts here-documents for a linked list of redirects
 * Description:
 * - Traverses the linked list of redirects, initiating here-documents for each
 * - Calls <here_doc> for each RD_HEREDOC type in the redirect list
 * Parameters:
 * - <redirect>: pointer to the head of the redirect list
 * Returns:
 * - 1 if all here-documents are successfully processed
 * - 0 if any here-doc fails or an allocation error occurs
 */
static int	start_heredoc(t_shell *shell, t_redirect *redirect)
{
	while (redirect)
	{
		if (redirect->type == RD_HEREDOC)
			if (!here_doc(shell, redirect))
				return (0);
		redirect = redirect->next;
	}
	return (1);
}

/**
 * Function that processes here-documents in a list of tokens
 * Description:
 * - Iterates through tokens to find commands with associated here-documents
 * - For each command, calls <start_heredoc> on its redirects
 * Parameters:
 * - <tokens>: array of tokens to process
 * - <size>: number of tokens in the array
 * Returns:
 * - 1 if all here-documents are successfully read and stored
 * - 0 if any here-doc fails or an error occurs
 */
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
