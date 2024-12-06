/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:22:34 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/06 16:27:49 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_standalone_print(char *env_var)
{
	char	*equal;

	equal = ft_strchr(env_var, '=');
	if (equal)
	{
		(void)!write(1, env_var, (equal - env_var) + 1);
		if (*(equal + 1) != '\"')
			printf("\"%s\"\n", equal + 1);
		else
			printf("%s\n", equal + 1);
	}
	else
		printf("%s\n", env_var);
}
