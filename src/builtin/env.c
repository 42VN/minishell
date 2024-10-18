/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:49:27 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/18 16:10:37 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

static int export_print_sorted(char **envp)
{
	int		i;
	char	**sorted_envp;

	i = 0;
	sorted_envp = env_dup_sorted(envp);
	if (!sorted_envp)
		return (1);
	while (sorted_envp[i])
	{
		printf("%s\n", sorted_envp[i]);

		// if (sorted_envp[i][0] != '\0')
		// {
		// }
		++i;
	}
}

int	builtin_export(t_shell *shell, char **args)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (!args[0])
		return (export_print_sorted(shell->envp));
}
 