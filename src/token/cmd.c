/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:29:53 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/31 13:23:33 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtin.h"
#include "../../include/minishell.h"


static void	ft_quote_err(char quote, t_shell *shell)
{
	shell->err_type = ERR_SYNTAX;
	ft_printf_fd(2, "minishell: unexpected EOF while ");
	ft_printf_fd(2, "looking for matching `%c'\n", quote);
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
				return (ft_quote_err(*quote, shell), NULL);
		}
		start++;
	}
	res = ft_substr(*ptr, 0, start - (*ptr));
	if (!res)
		return (ft_error_ret("ft_make_str_cmd: malloc", shell, ERR_MALLOC, 0), NULL);
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
	res = (char *)ft_calloc(1, sizeof(char) * (len + 1)); // Allocate enough memory
	if (!res)
		return (ft_error_ret("ft_alter_quote: malloc", shell, ERR_MALLOC, 0), NULL);
	while (cmd[i])
	{
		if (cmd[i] != quote)
		{
			res[j] = cmd[i];
			++j;
		}
		++i;
	}
	res[j] = '\0';
	return (res);
}

static char	*ft_get_str_cmd(char **ptr, t_shell *shell)
{
	char 	*str;
	char	*res;
	char	quote;

	quote = '\0';
	str = ft_make_str_cmd(ptr, shell, &quote);
	if (!str)
		return (NULL);
	if (quote != '\0')
	{
		res = ft_alter_quote(str, quote, shell, ft_strlen(str));
		if (!res)
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


/**
 * - Handles the creation or update of command tokens. 
 * - If there is no string in the token array
 * at the current index, a new command is created.
 * - Otherwise, the string is joined as an argument to the existing command.
 */
int	ft_token_handle_cmd(char **ptr, t_shell *shell)
{
	size_t			*index;
	char			*str;

	if (!**ptr)
		return (1);
	index = &shell->tokens->cur_pos;
	if (!ft_is_op(**ptr))
	{
		str = ft_get_str_cmd(ptr, shell);
		if (!str)
			return (0);
		if (index > 0 && shell->tokens->array[*index].type == CMD
			&& shell->tokens->array[*index].cmd)
		{
			if (!ft_token_join_cmd(&shell->tokens->array[*index], &str))
				return (ft_free_null_ret(&str, 0));
		}
		else
		{
			shell->tokens->array[*index].type = CMD;
			shell->tokens->array[*index].cmd = str;
		}
	}
	return (1);
}
