/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:35:10 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/17 00:33:53 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	replace_exp(
	char **cmd_arg,
	char **res,
	int is_exp)
{
	if (is_exp)
	{
		ft_free_null(cmd_arg);
		*cmd_arg = *res;
	}
	else
		free(*res);
}

static int	exp_process(t_shell *shell, char **res, char *cmd)
{
	char	*joined;
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

	if (*res)
		printf("Res: [%s]\n", res);
	free(res); //temp
	// replace_exp(&shell->tokens->array[i].split_cmd[j], &res, is_exp);
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
		while (shell->tokens->array[i].split_cmd[j])
		{
			exp_logic(shell, i, j);
			++j;
		}
		++i;
	}
}
