/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:01:21 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/20 13:28:40 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exp_valid_dollar_var(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

// void	exp_strip_quotes(char *str)
// {
// 	size_t	read;
// 	size_t	write;
// 	char	quote;

// 	read = 0;
// 	write = 0;
// 	while (str[read])
// 	{
// 		if (str[read] == '\"' || str[read] == '\'')
// 		{
// 			quote = str[read++];
// 			while (str[read] && str[read] != quote)
// 				str[write++] = str[read++];
// 			if (str[read] == quote)
// 				read++;
// 		}
// 		else
// 		{
// 			str[write++] = str[read++];
// 		}
// 	}
// 	str[write] = '\0';
// }

static int find_op_quote(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			return (*str);
		str++;
	}
	return (0);
}

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