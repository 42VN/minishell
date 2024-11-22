/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exit_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:29:33 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/23 13:31:53 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exit_status(int exit_status, t_minishell *minishell)
{
	minishell->exit_status = exit_status;
	ft_itoa(exit_status, minishell->exit_status_str, 10);
}
