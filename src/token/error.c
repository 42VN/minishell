/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:52:10 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/22 20:03:25 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redirect_err(char *ptr)
{
	if (!*ptr)
		ft_printf_fd(2,
			"minishell: syntax error near unexpected token `newline`\n");
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

static void	ft_pipe_err(char *ptr)
{
	if (!ptr)
		return ;
	if (*ptr == '|')
	{
		if (*(ptr + 1) == '|')
			ft_printf_fd(2,
				"minishell: syntax error near unexpected token ||\n");
		else
			ft_printf_fd(2,
				"minishell: syntax error near unexpected token |\n");
	}
	
}

int	ft_syntax_err_ret(t_shell *shell, t_syntax_err err, int code)
{
	shell->tokens->syntax_err = err;
	return (code);
}

void	ft_token_syntax_err(t_shell *shell, char *ptr)
{
	t_syntax_err	syntax_err;
	
	syntax_err = shell->tokens->syntax_err;
	if (ptr && shell->err_type != ERR_NONE && syntax_err != ERR_SYNTAX_NONE)
	{
		printf("Error in: [%s]\n", ptr);
		shell->err_type = ERR_SYNTAX;
		while (ft_isspace(*ptr))
			ptr++;
		if (syntax_err == ERR_SYNTAX_RD || syntax_err == ERR_SYNTAX_RD_PATH)
			ft_redirect_err(ptr);
		else if (*ptr == '(')
		{
			ptr++;
			if (*ptr == '(')
			{
				ft_printf_fd(2,
				"minishell: unexpected EOF while looking for matching `)'\n");
			}
			ft_printf_fd(2,
				"minishell: syntax error: unexpected end of file\n");
				
		}
		else if (*ptr == '|' || *ptr == '|')
			ft_pipe_err(ptr);
		else
			ft_printf_fd(2,
				"minishell: syntax error near unexpected token %c\n", *ptr);
	}
}
