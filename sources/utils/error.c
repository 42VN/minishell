/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:57:37 by hitran            #+#    #+#             */
/*   Updated: 2024/09/09 15:33:10 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_msh(t_msh *msh)
{
	if (!msh)
		return ;
	if (msh->envp)
	{
		ft_free_triptr(&msh->envp);	
		// if (msh->envp->path)
		// 	free(msh->envp->path);
	}
}
void	exit_error(t_msh *msh, char *str, int n)
{
	if (msh)
		free_msh(msh);
	ft_printf_fd(2, "msh: %s\n", str);
	exit(n);
}