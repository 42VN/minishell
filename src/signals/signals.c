/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:58:02 by hitran            #+#    #+#             */
/*   Updated: 2024/11/19 22:27:03 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	event(void)
{
	return (0);
}

static void	set_signal_exit(t_shell *shell, int signal_number)
{
	static t_shell	*shell_struct;

	if (!shell)
		shell_struct->exitcode = signal_number + 128;
	else
		shell_struct = shell;
}

static void	sig_handler_heredoc(int signal_number)
{
	if (signal_number == SIGINT)
	{
		// ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_done = 1;
		set_signal_exit(NULL, SIGINT);
	}
}

static void	sig_parent_handler(int signal_number)
{
	if (signal_number == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		if (!isatty(STDIN_FILENO) || errno != EINTR)
			return ;
		set_signal_exit(NULL, SIGINT);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

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
	set_signal_exit(shell,SIGINT);
	shell->aborted = 1;
	if (type == PARENT && !set_parent())
		return (0);
	else if (type == CHILD && (signal(SIGINT, SIG_DFL) == SIG_ERR 
			|| signal(SIGQUIT, SIG_DFL) == SIG_ERR))
		return (0);
	else if (type == HEREDOC)
	{
		rl_event_hook = event;
		if (signal(SIGINT, sig_handler_heredoc) == SIG_ERR)
			return (0);
	}
	shell->aborted = 0;
	return (1);
}
