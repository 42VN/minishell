/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:35:10 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/27 13:53:35 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int exp_post_process(char **res, int i)
{
	char	quote;

	quote = '\0';
    if (!res || !(*res))
    {
		return (0);
	}
    while ((*res)[i])
    {
        if ((*res)[i] == '\'' || (*res)[i] == '\"')
        {
            quote = (*res)[i];
			break;
        }
        ++i;
    }
	if (quote != '\0')
	{
		i = exp_strip_quotes(*res, quote);
		// printf("Last quote: [%s] [%d] [%c]\n", *res, i, (*res)[i] ? (*res)[i] : '\0');
		if (i >= 0 && (*res)[i] != '\0')
		{
			exp_post_process(res, i);
		}
	}
    return (1);
}



static int	exp_process(t_shell *shell, char **res, char *cmd)
{
	size_t	k;

	k = 0;
	if (*cmd == '~')
		exp_tiddle_front(shell, res, cmd, &k);
	while (cmd[k])
	{
		
		if (cmd[k] == '$')
			exp_dollar(shell, res, cmd, &k);
		else if (cmd[k] == '~')
			exp_tiddle(res, cmd, &k);
		else if (cmd[k] == '\'')
			exp_single_quote(res, cmd, &k);
		else if (cmd[k] == '\"')
			exp_double_quote(shell, res, cmd, &k);
		else
			exp_normal(res, cmd, &k);
	}
	return (1);
}

static int	exp_logic(t_shell *shell, int i, int j)
{
	char	*res;

	res = ft_strdup("");
	if (!res)
		return (ft_error_ret("expansion: malloc", shell, ERR_MALLOC, 0));
	exp_process(shell, &res, shell->tokens->array[i].split_cmd[j]);
	if (!res)
		return (ft_error_ret("expansion below: malloc", shell, ERR_MALLOC, 0));
	exp_post_process(&res, 0);
	ft_free_null(&shell->tokens->array[i].split_cmd[j]);
	shell->tokens->array[i].split_cmd[j] = res;
	return (1);
}

void	expansion(t_shell *shell)
{
	size_t	i;
	size_t	j;
	
	if (!shell || shell->err_type != ERR_NONE)
		return ;
	i = 0;
	j = 0;
	while (i <= shell->tokens->cur_pos)
	{
		if (shell->tokens->array[i].split_cmd)
		{
			j = 0;
			while (shell->tokens->array[i].split_cmd[j])
			{
				exp_logic(shell, i, j);
				++j;
			}
			cleanup_split_cmd(shell->tokens->array[i].split_cmd);
		}
		++i;
	}
}
