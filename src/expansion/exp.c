/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:35:10 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/04 13:01:12 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expansion_redirect(t_shell *shell, size_t i)
{
	t_redirect	*redirect;

	redirect = NULL;
	if (shell->tokens->array[i].redirect)
	{
		redirect = shell->tokens->array[i].redirect;
		while(redirect)
		{
			if (redirect->type == HEREDOC)
			{
				exp_remove_quotes(&redirect->path, 0);
				redirect = redirect->next;
				continue;
			}
			if (redirect->path)
			{
				if (!exp_logic_str(shell, &redirect->path))
					return (0);
			}
			redirect = redirect->next;
		}
	}
	return (1);
}

static size_t	count_dollar(char **split_cmd)
{
	size_t	count;
	size_t	i;
	size_t	j;

	i = 0;
	count = 0;
	while (split_cmd[i])
	{
		j = 0;
		while (split_cmd[i][j])
		{
			if (split_cmd[i][j] == '$')
				++count;
			++j;
		}
		++i;
	}
	return (count);
}

static int	expansion_cmd_preprocess(char **split_cmd)
{
	int	remove_quote;
	int	i;

	remove_quote = 1;
	i = 0;
	while (split_cmd[i])
	{
		if (ft_strncmp(split_cmd[i], "export", ft_strlen("export")) == 0)
			return (0);
		else if (ft_strncmp(split_cmd[i], "echo", ft_strlen("echo")) == 0)
			return (0);
		++i;
	}
	return (1);
}
/**
 * Post processing fort cmd expansion string
 * 
 * Description: Remove leading empty string
 */
static int	expansion_cmd_postprocess(t_shell *shell, size_t i, size_t dollar_count)
{
	size_t	k;

	k = 0;
	if (shell->tokens->array[i].split_cmd[0])
	{
		if (!shell->tokens->array[i].split_cmd[0][0])
		{
			cleanup_split_cmd(shell->tokens->array[i].split_cmd);
			free(shell->tokens->array[i].split_cmd[k]);
			if (dollar_count > 0)
				shell->tokens->array[i].split_cmd[0] = ft_strdup("echo");
			else
				shell->tokens->array[i].split_cmd[0] = ft_strdup("");
			if (!shell->tokens->array[i].split_cmd[0])
					return (ft_error_ret("expansion: expansion_cmd: malloc", shell, ERR_MALLOC, 0));
		}
		++k;
	}
	return (1);
}

/**
 * Expansion for cmd and cmd args
 * 
 * Description:
 * 
 * -	Create and add new post-expansion string to new split cmd array (2d array)
 */
static int	expansion_cmd(t_shell *shell, size_t i)
{
	size_t	j;
	size_t	len;
	char	**new_split_cmd;

	j = 0;
	len = 0;
	if (shell->tokens->array[i].split_cmd)
	{
		while (shell->tokens->array[i].split_cmd[len])
			len++;
		new_split_cmd = (char **)ft_calloc(1, (len + 1) * sizeof(char *));
		if (!new_split_cmd)
			return (ft_error_ret("expansion: expansion_cmd: ft_calloc", shell, ERR_MALLOC, 0));
		while (shell->tokens->array[i].split_cmd[j])
		{
			if (!exp_logic_split_str(shell, &shell->tokens->array[i].split_cmd[j], &new_split_cmd))
				return (0);
			++j;
		}
		ft_multi_free_null(&shell->tokens->array[i].split_cmd);
		shell->tokens->array[i].split_cmd = new_split_cmd;
	}
	return (1);
}

int	expansion_heredoc(t_shell *shell)
{
	size_t	i;
	
	if (!shell || shell->err_type != ERR_NONE)
		return (0);
	i = 0;
	
	while (i <= shell->tokens->cur_pos)
	{
		if (!expansion_redirect(shell, i))
			return (0);
		++i;
	}
	return (1);
}


int	expansion(t_shell *shell)
{
	size_t	i;
	
	if (!shell || shell->err_type != ERR_NONE)
		return (0);
	i = 0;
	
	while (i <= shell->tokens->cur_pos)
	{
		if (!expansion_redirect(shell, i))
			return (0);
		if (!expansion_cmd(shell, i))
			return (0);
		++i;
	}
	return (1);
}
