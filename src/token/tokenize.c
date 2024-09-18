/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:15:01 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/18 18:03:59 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_token_init(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell || !shell->tokens)
        return (0);
	shell->tokens->size = 10;
	shell->tokens->to_add = 10;
	shell->tokens->cur_pos = 0;
	shell->tokens->cur_token = 0;
	shell->tokens->array
		= (t_token *)ft_calloc(shell->tokens->size, sizeof(t_token));
	if (!shell->tokens->array)
	{
		shell->err_type = ERR_MEMORY;
		ft_token_free(shell);
		return (0);
	}
	return (1);
}

/**
 * Function that add a new token
 * Description:
 * -	Adding a new token to the allocated array
 * -	Reallocating the array if extension is needed
 * -	Changing the input by taking the pointer <p_input>
 */
int	ft_token_add(t_shell *shell, char **input)
{
	char			*start;
	char			*str;

	start = *input;
	if (!ft_token_categorize(shell, *input, start))
		return (0);
	return (1);
}

static int	tokenize_loop(t_shell *shell, char *line, char **arr)
{
	char	*substr;
	int		i;

	i = 0;
	while (arr[i])
	{
		substr = arr[i];
		if (*substr)
		{
			if (!ft_token_add(shell, &substr))
			{
				return (ft_error_ret("tokenize: ft_token_add",
					shell, ERR_MEMORY, 0));
			}
		}
		++i;
	}
	return (1);
}

int	tokenize(t_shell *shell, char *line)
{
	char	**arr;

	if (!shell || !line || !*line)
		return (0);
	shell->tokens = ft_calloc(1, sizeof(t_tokens));
	if (!shell->tokens)
		return (ft_error_ret("malloc", shell, ERR_MEMORY, 0));
	arr = ft_split_esc(line, ' ', 0);
	if (!arr)
	{
		free(shell->tokens);
		return (ft_error_ret("tokenize: ft_split_esc",
			shell, ERR_MEMORY, 0));
	}
	if (!ft_token_init(shell))
	{
		return (0);
	}
	if (tokenize_loop(shell, line, arr) == 0)
	{
		ft_multi_free_null(&arr);
		ft_token_free(shell);
		return (0);
	}
	ft_multi_free_null(&arr);
	return (1);
}
