/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:53:33 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/21 15:14:12 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_unset(t_shell *shell, char **split_cmd)
{
	int		i;
	char	*equal;
	char	*key;

	i = 1;
	if (!split_cmd[1])
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
}
