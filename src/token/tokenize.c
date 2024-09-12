/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:15:01 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/12 15:37:40 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_token_init(t_shell *shell)
{
	shell->tokens->size = 10;
	shell->tokens->to_add = 10;
	shell->tokens->cur_pos = 0;
	shell->tokens->cur_token = 0;
	shell->tokens->array = (t_token *)ft_calloc(shell->tokens->size, sizeof(t_token));
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
	int				index;
	char			*str;

	start = *input;
	index = shell->tokens->cur_pos;
	if (index > 0 && shell->tokens->need_join)
	{
		str = shell->tokens->array[index - 1].str;
		shell->tokens->array[index - 1].str = ft_strjoin(str ,*input);
		free(str);
		if (!shell->tokens->array[index - 1].str)
		{
			shell->err_type = ERR_MEMORY;
			return (0);
		}
		shell->tokens->need_join = 0;
		return (1);
	}
	if (!ft_token_categorize(shell, *input, start))
		return (0);
	return (1);
}

static int	tokenize_loop(t_shell *shell, char **av)
{
	int		i;
	char	*input;
	
	i = 1;
	while (av[i])
	{
		input = av[i];
		ft_skip_strchr((const char **)&input, ' ');
		if (*input)
		{
			if (!ft_token_add(shell, &input))
				return (0);
		}
		++i;
	}
	return (1);
}

int	tokenize(t_shell *shell, char **av)
{
	if (!shell || !av || !*av)
		return (0);
	shell->tokens = ft_calloc(1, sizeof(t_tokens));
	if (!shell->tokens)
	{
		shell->err_type = ERR_MEMORY;
		return (0);
	}
	if (!ft_token_init(shell))
		return (0);
	if (tokenize_loop(shell, av) == 0)
	{
		ft_token_free(shell);
		return (0);
	}
	return (1);
}
