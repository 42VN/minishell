/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:27:01 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/28 17:59:44 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_make_str_cmd(char **ptr, t_shell *shell, char *quote)
{
	char	*res;
	char	*start;
	char	*quote_end;

	start = *ptr;
	while (*start && !ft_isspace(*start) && !ft_is_op(*start))
	{
		if (*start == '\'' || *start == '\"')
		{
			*quote = *start;
			quote_end = ft_strchr(start + 1, *start);
			if (quote_end)
				start = quote_end;
			else
				return (ft_quote_err(start, shell, ptr));
		}
		start++;
	}
	res = ft_substr(*ptr, 0, start - (*ptr));
	if (!res)
		return (ft_error_ret_null("ft_make_str_cmd: malloc", shell, ERR_MALLOC));
	*ptr = start;
	return (res);
}

/**
 * Function to parse one string token from an input string
 * and move the pointer of the input string
 * 
 * Description:
 * 
 * -	Remove the most outer quotes, only take the inner string including 
 * inner quotes
 */
char	*ft_token_parse(char **ptr, t_shell *shell, int remove_quote)
{
	char	*str;
	char	*res;
	char	quote;

	quote = '\0';
	str = ft_make_str_cmd(ptr, shell, &quote);
	if (!str)
		return (NULL);
	if (quote != '\0' && remove_quote == 1)
	{
		res = ft_remove_quote(str, quote, shell, ft_strlen(str));
		if (!res && shell->err_type == ERR_MALLOC)
		{
			free(str);
			return (NULL);
		}
		free(str);
	}
	else
		res = str;
	return (res);
}
