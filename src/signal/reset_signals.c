/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 22:35:25 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/06 22:50:10 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell_signal.h"

/**
 * Reset all signal handlers to default.
*/
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
