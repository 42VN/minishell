/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_ret.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:14:53 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/29 14:44:11 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_error_ret(
	char *str,
	t_shell *shell,
	t_err_type type,
	int return_code)
{
	if (shell && type != ERR_NONE)
		shell->err_type = type;
	ft_printf_fd(2, "minishell: %s\n", str);
	return (return_code);
}
