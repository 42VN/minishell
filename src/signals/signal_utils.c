/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:58:02 by hitran            #+#    #+#             */
/*   Updated: 2024/12/16 15:59:24 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	event(void)
{
	return (0);
}
static t_shell *g_current_shell = NULL;

void	set_signal_exit(t_shell *shell)
{
    if (shell)
        g_current_shell = shell;
    else if (g_current_shell)
        g_current_shell->exitcode = SIGINT + 128;
}

void	sig_heredoc_handler(int signal_number)
{
	if (signal_number == SIGINT)
	{
		// printf("hd handler\n");
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_done = 1;
		set_signal_exit(NULL);
	}
}

void	sig_parent_handler(int signal_number)
{
	if (signal_number == SIGINT)
	{
				// printf("pr handler\n");
		ft_putstr_fd("\n", STDOUT_FILENO);
		if (!isatty(STDIN_FILENO) || errno != EINTR)
			return ;
		set_signal_exit(NULL);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_afterhd_handler(int signal_number)
{
	if (signal_number == SIGINT)
	{
				// printf("after handler\n");
		// ft_putstr_fd("\n", STDOUT_FILENO);
		if (!isatty(STDIN_FILENO) || errno != EINTR)
			return ;
		set_signal_exit(NULL);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}