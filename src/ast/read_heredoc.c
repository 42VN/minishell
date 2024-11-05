/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:22:42 by jazevedo          #+#    #+#             */
/*   Updated: 2024/11/05 13:07:35 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_and_free(char *s1, char *s2)
{
	char	*tmp;
	char	*res;

	if (!s1)
		tmp = ft_strdup(s2);
	else
		tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (NULL);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	res = ft_strjoin(tmp, "\n");
	if (tmp)
		free(tmp);
	return (res);
}

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
		// printf("%s\n", heredoc);
	}
	if (!here_doc)
		return (0);
	free(redirect->path);
	redirect->path = heredoc;
	return (1);
}

int	start_heredoc(t_redirect *redirect)
{
	while (redirect)
	{
		// printf("type = %s\n", redirect_string(redirect->type));
		if (redirect->type == RD_HEREDOC)
			if (!here_doc(redirect))
				return (0);
		redirect = redirect->next;
	}
	return (1);
}

int	read_heredoc(t_token *tokens, int size)
{
	int	index;

	index = 0;
	while (index < size)
	{
		// printf("index = %d, sizze = %d\n", index, size);
		if (tokens[index].type == CMD)
		{
			// printf("cmd = %s\n", tokens[index].cmd);
			if (!start_heredoc(tokens[index].redirect))
				return (0);
		}
		index++;
	}
	return (1);
}
