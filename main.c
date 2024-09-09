/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:18:34 by hitran            #+#    #+#             */
/*   Updated: 2024/09/09 15:34:52 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int g_errno = 0;

static void	minishell(char **envp)
{
	t_msh *msh;

	msh = ft_calloc(sizeof(t_msh), 1);
	if (!msh)
		exit_error(NULL, "Memory allocation failed", 1);
	g_errno = 0;
	getcwd(msh->cwd, CWD_SIZE);
	msh->envp = ft_matrix_dup(envp, ft_matrixlen(envp));
	wait_signal(1);
	while (1)
		parse_input(msh);
	rl_clear_history();
}

int	main(int ac, char **av, char **envp)
{
	if (ac != 1)
	{
				// exit_error(msh, "Invalid number of arguments.", g_errno);

		ft_printf_fd(2, "msh: %s: Invalid number of arguments.\n", av[0] +2);
		exit (EXIT_FAILURE);
	}
	minishell(envp);
	exit (EXIT_SUCCESS);
}
