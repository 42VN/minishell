/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:01:17 by hitran            #+#    #+#             */
/*   Updated: 2024/09/04 12:27:39 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static  void	exit_error(char *str, int n)
{
	ft_printf_fd(2, "msh: %s\n", str);
	exit(n);
}

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

static void	init_msh(t_minishell *msh, char **envp)
{
	msh->envp = ft_matrix_dup(envp, ft_matrixlen(envp));
	if (!msh->envp)
	{
		free(msh);
		exit_error("Envp duplication failed", 1);
	}
	msh->path = find_envp_path(envp);
	msh->level = get_shell_level(envp) + 1;
}

void minishell(char **envp)
{
	t_minishell *msh;

	msh = ft_calloc(sizeof(t_minishell), 1);
	if (!msh)
		exit_error("Memory allocation failed", 1);
	init_msh(msh, envp);
}
