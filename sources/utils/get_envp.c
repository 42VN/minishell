/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:01:17 by hitran            #+#    #+#             */
/*   Updated: 2024/09/09 15:31:15 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_envp_path(char **envp)
{
	while (*envp && !ft_strnstr(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		return (ft_strdup("./"));
	return (ft_substr(*envp, 5, ft_strlen(*envp) - 5));
}

static int	get_shell_level(char **envp)
{
	while (*envp && !ft_strnstr(*envp, "SHLVL=", 6))
		envp++;
	return (ft_atoi(ft_strchr(*envp, '=') + 1));
}

void	get_envp(t_msh *msh, char **envp)
{
	msh->envp->array = ft_matrix_dup(envp, ft_matrixlen(envp));
	if (!msh->envp->array)
		exit_error(msh, "Envp duplication failed", 1);
	msh->envp->path = find_envp_path(envp);
	msh->envp->level = get_shell_level(envp) + 1;
}
