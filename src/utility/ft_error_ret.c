/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_ret.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:14:53 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/07 21:26:31 by hitran           ###   ########.fr       */
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

char	*ft_error_ret_null(
	char *str,
	t_shell *shell,
	t_err_type type)
{
	if (shell && type != ERR_NONE)
		shell->err_type = type;
	ft_printf_fd(2, "minishell: %s\n", str);
	return (NULL);
}
