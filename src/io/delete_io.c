/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:02:45 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/19 21:09:58 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include <stdlib.h>

void	delete_io(void *io)
{
	if (io == NULL)
		return ;
	free(((t_io *)io)->token);
	free(io);
}
