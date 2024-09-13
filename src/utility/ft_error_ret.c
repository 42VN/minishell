/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_ret.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:13:26 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/12 18:11:08 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_error_ret(
	char *str,
	t_shell *shell,
	t_err_type type,
	int return_code)
{
	if (shell && type)
	{
		shell->err_type = type;
	}
	ft_printf_fd(2, "Error: %s\n", str);
	return (return_code);
}
