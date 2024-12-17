/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:58:02 by hitran            #+#    #+#             */
/*   Updated: 2024/12/17 15:17:09 by ktieu            ###   ########.fr       */
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

int	start_signal(t_shell *shell, t_signal_type type)
{
	set_signal_exit(shell);
	shell->aborted = 1;
	if (type == PARENT && !set_parent())
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


//HOANG SIGNAL

void	sigint_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler_heredoc(int signum)
{
	(void)signum;
	close(STDIN_FILENO);
	// write(STDOUT_FILENO, "\n", 1);
}

int	reset_signals(void)
{
	const int			signums[] = {SIGINT, SIGQUIT};
	struct sigaction	sa;
	int					i;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	i = 0;
	while (i < 2)
	{
		if (sigaction(signums[i], &sa, NULL) < 0)
		{
			perror("minishell: sigaction");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	set_signal_handler(int signum, void (*handler)(int))
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	if (sigaction(signum, &sa, NULL) < 0)
	{
		perror("minishell: sigaction");
		return (-1);
	}
	return (0);
}

