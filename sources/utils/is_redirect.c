/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:39:46 by hitran            #+#    #+#             */
/*   Updated: 2024/09/11 14:49:45 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_if(t_token_type type)
{
	return (type == RD_IN || type == RD_OUT
			|| type == RD_HEREDOC || type == RD_APPEND);
}
