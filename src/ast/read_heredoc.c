/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:22:42 by jazevedo          #+#    #+#             */
/*   Updated: 2024/11/08 11:44:33 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
char	*join_and_free(char *s1, char *s2)
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
int	here_doc(t_redirect *redirect)
{
	char	*line;
	char	*heredoc;

	heredoc = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(redirect->path, line))
		{
			free(line);
			break ;
		}
		heredoc = join_and_free(heredoc, line);
	}
	if (!heredoc)
		return (0);
	free(redirect->path);
	redirect->path = heredoc;
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
int	start_heredoc(t_redirect *redirect)
{
	while (redirect)
	{
		if (redirect->type == RD_HEREDOC)
			if (!here_doc(redirect))
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
int	read_heredoc(t_token *tokens, int size)
{
	int	index;

	index = 0;
	while (index < size)
	{
		if (tokens[index].type == CMD)
		{
			if (!start_heredoc(tokens[index].redirect))
				return (0);
		}
		index++;
	}
	return (1);
}
