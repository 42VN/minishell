/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:44:55 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/19 16:46:59 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_quote_err(char *quote, t_shell *shell, char **ptr)
{
	shell->err_type = ERR_SYNTAX;
	ft_printf_fd(2, "minishell: unexpected EOF while ");
	ft_printf_fd(2, "looking for matching `%c'\n", *quote);
	*ptr = quote;
	return (NULL);
}

/**
 * Function to remove the most outer enclosing quotes
 * Only works if the first character is a quote
 */
char	*ft_remove_quote(
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
		return (ft_error_ret("ft_remove_quote: malloc",
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