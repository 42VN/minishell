/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:52:10 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/27 16:47:12 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_token_parse_error(char *ptr)
{
	char	*start;
	char	*str;
	size_t	len;

	ft_skip_strchr(&ptr, ' ');
	start = ptr;
	while (!ft_isspace(*ptr) && *ptr != '\0')
		ptr++;
	len = ptr - start;
	str = ft_substr(start, 0, len);
	if (!str)
		ft_printf_fd(2, "minishell: ft_token_parse_error: malloc\n");
	if (*str)
		ft_printf_fd(2, "minishell: op parse error near %s\n", str);
	else
		ft_printf_fd(2, "minishell: op parse error near newline\n");
	free(str);
}
