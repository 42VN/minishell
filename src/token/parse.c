/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:27:01 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/08 19:42:31 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_quote_err(char *quote, t_shell *shell, char **ptr)
{
	shell->err_type = ERR_SYNTAX;
	ft_printf_fd(2, "minishell: unexpected EOF while ");
	ft_printf_fd(2, "looking for matching `%c'\n", *quote);
	*ptr = quote;
	return (NULL);
}

static char	*ft_make_str_cmd(char **ptr, t_shell *shell, char *quote)
{
	char	*res;
	char	*start;
	char	*quote_end;
	size_t	len;

	len = 0;
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
		return (ft_error_ret_null("ft_make_str_cmd: malloc", shell, 0));
	*ptr = start;
	return (res);
}

/**
 * Function to remove the most outer enclosing quotes
 * Only works if the first character is a quote
 */
static char	*ft_alter_quote(
	char *cmd,
	char quote,
	t_shell *shell,
	size_t len)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	res = (char *)ft_calloc(1, sizeof(char) * (len + 1));
	if (!res)
		return (ft_error_ret("ft_alter_quote: malloc",
				shell, ERR_MALLOC, 0), NULL);
	while (cmd[i])
	{
		if (cmd[i] != quote)
		{
			res[j] = cmd[i];
			++j;
		}
		++i;
	}
	if (j != 0)
		res[j] = '\0';
	else
		ft_bzero(res, len);
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
char	*ft_token_parse(char **ptr, t_shell *shell, int parse_quote)
{
	char	*str;
	char	*res;
	char	quote;

	quote = '\0';
	str = ft_make_str_cmd(ptr, shell, &quote);
	if (!str)
		return (NULL);
	if (quote != '\0' && parse_quote == 1)
	{
		res = ft_alter_quote(str, quote, shell, ft_strlen(str));
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
