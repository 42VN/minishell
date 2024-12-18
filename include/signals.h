/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:08:06 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/18 10:28:13 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

typedef struct s_shell	t_shell;

//---------------------------------||  SIGNAL ||------------------------------//
int		init_signals(void);
int		set_signals(int signum, void (*handler)(int));
int		default_signals(void);
int		heredoc_signal(t_shell *shell);
void	sigint_heredoc_handler(int signum);
void	sigint_handler(int signum);

//---------------------------------||  UTILS  ||------------------------------//
void	set_signal_exit(t_shell *shell);

#endif