/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:53:33 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/05 21:31:15 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	builtin_unset_check(t_shell *shell, char **split_cmd)
{
	if (!split_cmd[1])
		return (0);
	if (split_cmd[1] && split_cmd[1][0] == '-')
	{
		ft_printf_fd(2, "bash: unset: %s: invalid option\n", split_cmd[1]);
		update_status(shell, 2);
		return (0);
	}
	return (1);
}


void	builtin_unset(t_shell *shell, char **split_cmd)
{
	int		i;
	char	*equal;
	char	*key;

	i = 1;
	if (!builtin_unset_check(shell, split_cmd))
		return ;
	while (split_cmd[i])
	{
		equal = ft_strchr(split_cmd[i], '=');
		key = ft_substr(split_cmd[i], 0, equal - split_cmd[i]);
		if (!key)
		{
			update_status(shell, ft_error_ret("ft_builtin_unset: malloc", 
				shell, ERR_MALLOC, 1));
			return ;
		}
		equal = NULL;
		env_unset(shell, key);
		ft_free_null(&key);
		++i;
	}
	update_status(shell, 0);
}
