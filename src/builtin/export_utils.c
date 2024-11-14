/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 19:22:34 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/14 17:54:19 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_check_value(t_shell *shell, char **value_str)
{
	
	if (!*value_str)
		return ;
	if (ft_isspace(**value_str) || !(**value_str))
		*value_str = NULL;
	if ((**value_str == '\'' || **value_str=='\"')
		&& (*(*value_str + 1) == '\'' || *(*value_str + 1)=='\"'))
	{
		*value_str = NULL;
	}
}

void export_standalone_print(char *env_var)
{
	char	*equal;
	
	equal = ft_strchr(env_var, '=');
	if (equal)
	{
		write(1, env_var, (equal - env_var) + 1);
		if (*(equal + 1) != '\"')
			printf("\"%s\"\n", equal + 1);
		else
			printf("%s\n", equal + 1);
	}
	else
		printf("%s\n", env_var);
}