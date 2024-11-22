/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 13:34:48 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/20 15:00:14 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "command.h"
#include "utils.h"

static void	convert(char *str)
{
	char	*pipe;

	pipe = find_symbol(str, "|");
	if (pipe == NULL)
	{
		while (*str != '\0')
		{
			if (*str == '|')
				*str = 31;
			str++;
		}
		return ;
	}
	while (str != pipe)
	{
		if (*str == '|')
			*str = 31;
		str++;
	}
	convert(pipe + 1);
}

static void	recover(char **splits)
{
	char	*temp;

	while (*splits != NULL)
	{
		temp = *splits;
		while (*temp != '\0')
		{
			if (*temp == 31)
				*temp = '|';
			temp++;
		}
		splits++;
	}
}

static int	init_list(t_list *list, char **splits)
{
	int			i;
	t_command	*cmd;

	i = 0;
	while (splits[i] != NULL)
	{
		cmd = new_cmd(splits[i]);
		if (cmd == NULL)
			return (-1);
		if (ft_list_push(list, cmd) < 0)
		{
			delete_cmd(cmd);
			return (-1);
		}
		i++;
	}
	return (0);
}

t_list	*parse_cmd_list(const char *str)
{
	char	*dup;
	char	**splits;
	t_list	*list;

	dup = ft_strdup(str);
	if (dup == NULL)
		return (perror("minishell: malloc"), NULL);
	convert(dup);
	splits = ft_split(dup, '|');
	free(dup);
	if (splits == NULL)
		return (NULL);
	recover(splits);
	list = ft_list(0);
	if (list == NULL)
		return (ft_del_str_arr(&splits), NULL);
	if (init_list(list, splits) < 0)
	{
		ft_del_str_arr(&splits);
		ft_list_clear(&list, delete_cmd);
		return (NULL);
	}
	ft_del_str_arr(&splits);
	return (list);
}
