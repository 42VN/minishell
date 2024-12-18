/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herredoc_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:58:02 by hitran            #+#    #+#             */
/*   Updated: 2024/12/18 09:28:38 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	event(void)
{
	return (0);
}

int	heredoc_signal(t_shell *shell)
{
	set_signal_exit(shell);
	shell->aborted = 1;
	rl_event_hook = event;
	if (signal(SIGINT, sigint_heredoc_handler) == SIG_ERR)
		return (0);
	shell->aborted = 0;
	return (1);
}
