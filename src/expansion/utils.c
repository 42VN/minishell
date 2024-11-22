/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:01:21 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/22 12:00:09 by hitran           ###   ########.fr       */
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
			continue;
		}
		split_cmd[j++] = split_cmd[i++];
	}
	split_cmd[j] = NULL;
}

// static int find_op_quote(char *str)
// {
// 	while (*str)
// 	{
// 		if (*str == '\'' || *str == '\"')
// 			return (*str);
// 		str++;
// 	}
// 	return (0);
// }
//check

void	exp_strip_quotes(char *str, char c)
{
	size_t	read;
	size_t	write;

	read = 0;
	write = 0;
	if (!str || *str == '\0')
        return;
	if (c != '\'' && c != '\"')
		return ;
	while (str[read])
	{
		if (str[read] == c)
		{
			read++;
			while (str[read] && str[read] != c)
				str[write++] = str[read++];
			if (str[read] == c)
				read++;
		}
		else
		{
			str[write++] = str[read++];
		}
	}
	str[write] = '\0';
}

void ft_join_quote(char **res, char *quote)
{
	char	*joined;

	joined = ft_strjoin(*res, quote);
	if (!joined)
		return (ft_free_null(res));
	free(*res);
	*res = joined;
}