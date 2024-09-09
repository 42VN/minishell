/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:47:49 by hitran            #+#    #+#             */
/*   Updated: 2024/09/05 12:06:39 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "mylib.h"
# include <stdio.h>						// printf
# include <readline/readline.h>			// readline
# include <readline/history.h>			// readline
# include <signal.h>   					// SIGINT, SIGQUIT, SIGTERM, sigaction

extern int g_errno;

typedef struct s_msh
{
	char	**envp;
	char	*path;
	int		level;
}	t_msh;

void minishell(char **envp);

#endif