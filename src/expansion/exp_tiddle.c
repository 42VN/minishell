/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_tiddle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 00:17:05 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/06 16:52:18 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*exp_tiddle_home_path(t_shell *shell)
{
	char	*home_path;
	char	*exp_str;

	home_path = env_get(shell->envp, "HOME", 0);
	if (!home_path)
		exp_str = ft_strdup("");
	else
		exp_str = ft_strdup(home_path);
	if (!exp_str)
		return (0);
	return (exp_str);
}

/**
 * Function to append the HOME path to the expansion string
 * if the tiddle is at the front of the string
 * 
 * Description: Tiddle only returns HOME path
 * if it is at the front and there is no following character
 */
void	exp_tiddle_front(t_shell *shell, char **res, char *cmd, size_t *index)
{
	char	*str;
	char	*joined;
	size_t	i;

	i = *index;
	i++;
	str = NULL;
	if (cmd[i] == '\0' || ft_isspace(cmd[i]))
	{
		str = exp_tiddle_home_path(shell);
		if (!str)
			return (ft_free_null(res));
		joined = ft_strjoin(*res, str);
		if (!joined)
		{
			free(str);
			ft_free_null(res);
			return ;
		}
		ft_free_null(res);
		ft_free_null(&str);
		*res = joined;
		(*index)++;
	}
}

/**
 * Function to append more a tiddle in the expansion string
 */
void	exp_tiddle(char **res, char *cmd, size_t *i)
{
	char	*str;
	char	*joined;

	(void)cmd;
	(*i)++;
	str = ft_strdup("~");
	if (!str)
	{
		ft_free_null(res);
		return ;
	}
	joined = ft_strjoin(*res, str);
	if (!joined)
	{
		free(str);
		ft_free_null(res);
		return ;
	}
	free(*res);
	free(str);
	*res = joined;
}
