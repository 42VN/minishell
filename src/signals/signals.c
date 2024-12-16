/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:58:02 by hitran            #+#    #+#             */
/*   Updated: 2024/12/16 21:33:35 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_parent(void)
{
	struct sigaction	sa;

	rl_done = 0;
	rl_event_hook = NULL;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sig_parent_handler;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (0);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (0);
	return (1);
}

static int	set_afterhd(void)
{
	struct sigaction	sa;

	rl_done = 0;
	rl_event_hook = NULL;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sig_afterhd_handler;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (0);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (0);
	return (1);
}

int	start_signal(t_shell *shell, t_signal_type type)
{
	set_signal_exit(shell);
	shell->aborted = 1;
	if (type == PARENT && !set_parent())
		return (0);
	if (type == AFTER_HD && !set_afterhd())
		return (0);
	else if (type == CHILD && (signal(SIGINT, SIG_DFL) == SIG_ERR
			|| signal(SIGQUIT, SIG_DFL) == SIG_ERR))
		return (0);
	else if (type == HEREDOC)
	{
		rl_event_hook = event;
		if (signal(SIGINT, sig_heredoc_handler) == SIG_ERR)
			return (0);
	}
	shell->aborted = 0;
	return (1);
}
