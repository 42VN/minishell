/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:47:49 by hitran            #+#    #+#             */
/*   Updated: 2024/09/04 10:52:39 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "mylib.h"
# include <stdio.h>		// printf

typedef struct s_minishell
{
	char	**envp;
	char	*path;
	int		level;
}	t_minishell;

void minishell(char **envp);

#endif