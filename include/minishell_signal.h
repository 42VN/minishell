/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 22:29:40 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/17 22:59:17 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SIGNAL_H
# define MINISHELL_SIGNAL_H

# include <signal.h>

int		set_signal_handler(int signum, void (*handler)(int));
void	sigint_handler(int signum);
void	sigint_handler_heredoc(int signum);
int		reset_signals(void);

#endif
