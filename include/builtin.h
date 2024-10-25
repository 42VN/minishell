/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:32:25 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/25 22:58:23 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct s_shell	t_shell;

typedef enum e_builtin_type
{
	BI_UNDEFINED = 0,
	BI_CD = 1,
	BI_PWD = 2,
	BI_ECHO = 3,
	BI_EXIT = 4,
	BI_ENV = 5,
	BI_EXPORT = 6,
	BI_UNSET = 7
}	t_builtin_type;

t_builtin_type	get_builtin(char *str);
int				builtin_env(
					t_shell *shell,
					t_builtin_type type,
					char **split_cmd);
#endif
