/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:27:58 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/06 16:31:13 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	shell_init(t_shell *shell, char **envp)
{
	ft_memset(shell, 0, sizeof(t_shell));
	shell->envp = envp;
}