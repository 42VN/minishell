/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:27:37 by hitran            #+#    #+#             */
/*   Updated: 2024/12/17 13:28:18 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_status(t_shell *shell, int new_status)
{
	if (new_status >= 0)
		shell->exitcode = new_status;
	return (shell->exitcode);
}
