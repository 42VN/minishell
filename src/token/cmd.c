/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:29:53 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/28 20:24:29 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_next_space(char **ptr)
{
	int	has_space;

	has_space = 0;
	while (**ptr && ft_isspace(**ptr))
	{
		has_space = 1;
		(*ptr)++;
	}
	return (has_space);
}

static int	check_next_empty_cmd(char *ptr, t_shell *shell, char **str)
{
	char	*temp;
	char	*new_str;
	int 	hasspace;
	int		space_count;	
	
	hasspace = check_next_space(&ptr);
	space_count = ft_space_count(shell->tokens->array[shell->tokens->cur_pos].cmd);
	if (hasspace && space_count > 1 && (*ptr == '\'' || *ptr == '\"'))
	{
		temp = ft_token_parse(&ptr, shell, 1);
		if (!temp)
			return (ft_error_ret(
				"check_next_empty_cmd: ft_token_handle_cmd: malloc",
				shell, ERR_MALLOC, 0));
		if (!*temp)
		{
			shell->tokens->is_empty_cmd = 1;
			ft_free_null(str);
		}
		free(temp);
	}
	return (1);
}

static int	empty_cmd_handler(t_shell *shell, char **str)
{
	char	*res;

	shell->tokens->is_empty_cmd = 0;
	res = ft_strdup("' '");
	if (!res)
		return (ft_error_ret("empty_cmd_handler: ft_token_handle_cmd: malloc", shell, ERR_MALLOC, 0));
	free(*str);
	*str = res;
	return (1);
}

static int ft_token_handle_cmd_init(t_shell *shell, char **ptr, size_t **index, char **str)
{
	if (!**ptr)
		return (1);
	if (ft_is_op(**ptr))
		return (0);
	*index = &shell->tokens->cur_pos;
	*str = ft_token_parse(ptr, shell, 0);
	if (!str)
		return (0);
	return (1);
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

	if (!ft_token_handle_cmd_init(shell, ptr, &index, &str))
		return (0);
	if (shell->tokens->is_empty_cmd)
	{
		if (!empty_cmd_handler(shell, &str))
			return (0);
	}
	if (index && shell->tokens->array[*index].type == CMD //trung
		&& shell->tokens->array[*index].cmd)
	{
		if (!ft_token_join_cmd(&shell->tokens->array[*index], &str))
			return (ft_free_null_ret(&str, 0));
	}
	else
	{
		shell->tokens->array[*index].type = CMD;
		shell->tokens->array[*index].cmd = str;
		shell->tokens->is_empty_cmd = 0;
	}
	check_next_empty_cmd(*ptr, shell, &str);
	return (1);
}
