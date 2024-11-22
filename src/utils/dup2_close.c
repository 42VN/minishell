/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:15:05 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/15 14:33:52 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	dup2_close(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) < 0)
	{
		perror("minishell: dup2");
		close(oldfd);
		return (-1);
	}
	if (close(oldfd) < 0)
	{
		perror("minishell: close");
		return (-1);
	}
	return (0);
}
