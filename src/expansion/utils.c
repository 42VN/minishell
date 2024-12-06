/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:01:21 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/06 16:45:46 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exp_valid_dollar_var(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

/**
 * Function to clean up empty strings inside split_cmd
 */
void	cleanup_split_cmd(char **split_cmd)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (split_cmd[i] && split_cmd[i][0] == '\0')
		++i;
	if (!split_cmd[i])
		return ;
	i = 0;
	while (split_cmd[i])
	{
		if (split_cmd[i][0] == '\0')
		{
			free(split_cmd[i]);
			++i;
			continue ;
		}
		split_cmd[j++] = split_cmd[i++];
	}
	split_cmd[j] = NULL;
}

/*
 * Helper function to re-arrange the expansion string
*
 * Description:
 * -	Copy excuding the enclosing quotes.
 * -	Return the index of <last_quote> which will be processed
 * in the next <exp_remove_quotes> recursive function call.
 * */
static int	exp_strip_quote_overwrite(char *str, char c, int *read, int *write)
{
	int	last_quote;

	last_quote = -1;
	(*read)++;
	while (str[*read] && str[*read] != c)
		str[(*write)++] = str[(*read)++];
	if (str[*read] == c)
	{
		last_quote = *read - 1;
		(*read)++;
	}
	while (str[*read])
		str[(*write)++] = str[(*read)++];
	return (last_quote);
}

/*
 * Function to strip the quote in expansion string
 
 * Description:
 * -	Find the quote and its first occurrence
 * -	Strip the encosing quotes and re-arrange (shorten)
 * */
int	exp_strip_quotes(char *str, char c, int start)
{
	int	read;
	int	write;
	int	last_quote;

	read = start;
	write = start;
	last_quote = -1;
	if (!str || *str == '\0' || (c != '\'' && c != '\"'))
		return (0);
	while (str[read])
	{
		if (str[read] == c)
		{
			last_quote = exp_strip_quote_overwrite(str, c, &read, &write);
			break ;
		}
		else
			str[write++] = str[read++];
	}
	str[write] = '\0';
	return (last_quote);
}

void	ft_join_quote(char **res, char *quote)
{
	char	*joined;

	joined = ft_strjoin(*res, quote);
	if (!joined)
		return (ft_free_null(res));
	free(*res);
	*res = joined;
}
