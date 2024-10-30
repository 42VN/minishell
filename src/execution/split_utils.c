/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 12:56:32 by hitran            #+#    #+#             */
/*   Updated: 2024/10/30 21:07:55 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_all_white_spaces(char *s)
{
	while (*s)
	{
		if (*s != 32 && (*s < 9 || *s > 13))
			return (0);
		s++;
	}
	return (1);
}

void	handle_cmd_error(char **command, char *message, int free_pt)
{
	ft_printf_fd(2, "pipex: %s: %s\n", *command, message);
	if (free_pt)
		ft_free_triptr(&command);
	exit(127);
}

int	skip_quotes(char *str, int i)
{
	char	quote;

	quote = str[i];
	i++;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] != quote)
	{
		ft_printf_fd(2, "pipex: Missing %c\n", quote);
		exit (1);
	}
	return (i);
}

int	skip_word(char *str, int i)
{
	while (str[i] && str[i] != 32 && str[i] != 34 && str[i] != 39)
	{
		if (str[i] == '\\' && str[i + 1] != '\0')
			i += 2;
		else
			i++;
	}
	return (i);
}
