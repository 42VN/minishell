/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:52:10 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/06 15:10:49 by ktieu            ###   ########.fr       */
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
				"minishell: syntax error near unexpected token `>>'\n");
		else
			ft_printf_fd(2,
				"minishell: syntax error near unexpected token `>'\n");
	}
	else if (*ptr == '<')
	{
		if (*(ptr + 1) == '<')
			ft_printf_fd(2,
				"minishell: syntax error near unexpected token `<<'\n");
		else
			ft_printf_fd(2,
				"minishell: syntax error near unexpected token `<'\n");
	}
}

static void	ft_logic_err(char *ptr)
{
	if (*ptr == '|')
	{
		if (*(ptr + 1) == '|')
			ft_printf_fd(2,
				"minishell: syntax error near unexpected token `||'\n");
		else
			ft_printf_fd(2,
				"minishell: syntax error near unexpected token `|'\n");
	}
	else if (*ptr == '&')
	{
		if (*(ptr + 1) == '&')
			ft_printf_fd(2,
				"minishell: syntax error near unexpected token `&&'\n");
		else
			ft_printf_fd(2,
				"minishell: syntax error near unexpected token `&'\n");
	}
	else
		ft_printf_fd(2,
				"minishell: syntax error: unexpected end of file\n");
}

int	ft_syntax_err_ret(t_shell *shell, t_syntax_err err, int code)
{
	shell->err_type = ERR_SYNTAX;
	shell->tokens->syntax_err = err;
	return (code);
}

void	ft_token_syntax_err(t_shell *shell, char *ptr)
{
	t_syntax_err	syntax_err;
	
	syntax_err = shell->tokens->syntax_err;
	while (ft_isspace(*ptr))
		ptr++;
	if (shell->err_type == ERR_SYNTAX)
	{
		if (syntax_err == ERR_SYNTAX_RD)
			ft_redirect_err(ptr);
		else if (syntax_err == ERR_SYNTAX_LOGIC || (*ptr == '|' || *ptr == '&'))
			ft_logic_err(ptr);
		else if (syntax_err == ERR_SYNTAX_BR)
			ft_printf_fd(2,
				"minishell: syntax error: unexpected end of file\n");
		else
			ft_printf_fd(2,
				"minishell: syntax error near unexpected token `%c'\n", *ptr);
		shell->exitcode = 2;
	}
	shell->err_type = ERR_NONE;
}
