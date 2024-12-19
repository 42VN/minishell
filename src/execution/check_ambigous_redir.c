/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambigous_redir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:06:57 by hitran            #+#    #+#             */
/*   Updated: 2024/12/19 12:34:26 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ambigous_redir(t_shell *shell, t_redirect *redirect, int *fd)
{
	if (redirect->path && redirect->org_path)
	{
		if (!redirect->path[0] && redirect->org_path[0] 
			&& !inside_quotes(redirect->org_path)
			&& redirect->type != RD_HEREDOC)
			return (open_error(shell, redirect->org_path, fd,
					"ambiguous redirect"));
		else if (!ft_strcmp(redirect->org_path, "*"))
			return (open_error(shell, redirect->path, fd,
					"ambiguous redirect"));
		return (EXIT_SUCCESS);

	}
	return (EXIT_FAILURE);
}
