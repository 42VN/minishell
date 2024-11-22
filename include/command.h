/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:18:49 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/16 15:51:32 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "libft.h"

typedef struct s_command
{
	char	**argv;
	t_list	*io_list;
	t_bool	is_builtin;
}	t_command;

t_command	*new_cmd(const char *str);
void		delete_cmd(void *cmd);
size_t		count_arguments(t_command *cmd);
t_bool		check_builtin(const char *cmd);
t_bool		check_wildcard(const char *cmd);
char		**parse_cmd(const char *cmd);

#endif
