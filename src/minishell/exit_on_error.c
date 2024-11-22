/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_on_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:07:22 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/14 15:07:38 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_on_error(
	const char *err_src,
	const char *err_msg,
	t_minishell *minishell,
	int exit_code
)
{
	if (err_src != NULL)
		ft_fprintf(STDERR_FILENO, "minishell: %s: ", err_src);
	if (err_msg != NULL)
		ft_fprintf(STDERR_FILENO, "%s\n", err_msg);
	delete_minishell(minishell);
	exit(exit_code);
}
