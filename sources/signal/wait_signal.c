/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:01:17 by hitran            #+#    #+#             */
/*   Updated: 2024/09/09 11:10:07 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_errno = 1;
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

static void	child_handler(int signal)
{
	if (signal == SIGINT)
		g_errno = 130;
	else if (signal == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		g_errno = 131;
	}
	return ;
}

void	wait_signal(int i)
{
	struct sigaction	sa;

	if (i)
		sa.sa_handler = &signal_handler;
	else
		sa.sa_handler = &child_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}
