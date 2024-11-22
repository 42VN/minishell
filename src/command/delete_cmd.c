/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:26:51 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/15 16:35:11 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "io.h"

void	delete_cmd(void *cmd)
{
	t_command	*cmd_ptr;

	cmd_ptr = (t_command *)cmd;
	if (cmd_ptr == NULL)
		return ;
	ft_del_str_arr(&cmd_ptr->argv);
	ft_list_clear(&cmd_ptr->io_list, delete_io);
	free(cmd);
}
