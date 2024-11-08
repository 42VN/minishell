/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:52:10 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/08 19:43:00 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char *ft_parse_error_str(char *ptr)
// {
// 	char	*start;
// 	size_t	len;
// 	char	*res;
// 	start = ptr;
// 	len = 0;
// 	res = NULL;
// 	if (*start == '|' || *start == '&')
// 		len = 2;
// 	else
// 	{
// 		while (!ft_isspace(*ptr) && *ptr != '\0')
// 			ptr++;
// 		len = ptr - start;
// 	}
// 	if (len > 0)
// 		res = ft_substr(start, 0, len);
// 	return (res);
// }

static void	ft_redirect_err(char *ptr)
{
	if (!ptr)
		return ;
	if (*ptr == '>')
	{
		if (*(ptr + 1) == '>')
			ft_printf_fd(2,
				"minishell: syntax error near unexpected token >>\n");
		else
			ft_printf_fd(2,
				"minishell: syntax error near unexpected token >\n");
	}
	if (*ptr == '<')
	{
		if (*(ptr + 1) == '<')
			ft_printf_fd(2,
				"minishell: syntax error near unexpected token <<\n");
		else
			ft_printf_fd(2,
				"minishell: syntax error near unexpected token <\n");
	}
}

void	ft_token_parse_error(t_shell *shell, char *ptr)
{
	char	*str;

	shell->err_type = ERR_SYNTAX;
	while (ft_isspace(*ptr))
		ptr++;
	if (!ptr)
		ft_printf_fd(2,
			"minishell: syntax error near unexpected token newline\n");
	else if (*ptr == '(')
		ft_printf_fd(2, "minishell: syntax error caused by missing )\n");
	else if (*ptr == '>' || *ptr == '<')
		ft_redirect_err(ptr);
	else if (*ptr == '\'' || *ptr == '\"')
		ft_printf_fd(2, "minishell: syntax error: unexpected end of file\n");
	else
		ft_printf_fd(2,
			"minishell: syntax error near unexpected token %c\n", *ptr);
	free(str);
}
