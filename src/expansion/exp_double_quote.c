/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_double_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:20:20 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/19 13:22:41 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exp_double_quote(char **res, char *cmd, size_t *i)
{
	char	*joined;

	joined = ft_strjoin(*res, '\"');
	if (!joined)
		return (ft_free_null(res));
	
}