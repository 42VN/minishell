/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:21:12 by mito              #+#    #+#             */
/*   Updated: 2024/06/11 16:31:02 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "builtin.h"
#include "utils.h"

static int	handle_key_validation(const char *key)
{
	char	*eq_ptr;
	char	*export_key;

	eq_ptr = ft_strchr(key, '=');
	if (eq_ptr == NULL)
	{
		if (!is_valid_env_key(key))
		{
			ft_fprintf(2,
				"minishell: export: `%s': not a valid identifier\n", key);
			return (1);
		}
	}
	export_key = ft_substr(key, 0, eq_ptr - key);
	if (export_key == NULL)
		return (perror("minishell: ft_substr()\n"), 1);
	if (!is_valid_env_key(export_key))
	{
		ft_fprintf(2, "minishell: export: `%s': not a valid identifier\n", key);
		free(export_key);
		return (1);
	}
	free(export_key);
	return (0);
}

static int	add_node(t_list *env_list, t_list *export_list, const char *str)
{
	char	*cmd_dup;

	cmd_dup = ft_strdup(str);
	if (cmd_dup == NULL)
		return (-1);
	if (ft_list_push(export_list, cmd_dup) < 0)
	{
		free(cmd_dup);
		return (-1);
	}
	if (ft_strchr(str, '=') != NULL)
	{
		cmd_dup = ft_strdup(str);
		if (cmd_dup == NULL)
			return (-1);
		if (ft_list_push(env_list, cmd_dup) < 0)
		{
			free(cmd_dup);
			return (-1);
		}
	}
	return (0);
}

static int	update(
	const char *env_var,
	t_node *env_list_node,
	t_list *export_list
)
{
	t_node	*node;

	if (ft_strchr(env_var, '=') == NULL)
		return (0);
	free(env_list_node->data);
	env_list_node->data = ft_strdup(env_var);
	if (env_list_node->data == NULL)
		return (-1);
	node = ft_list_find(export_list, (void *)env_var, is_key_exist);
	if (node != NULL)
	{
		free(node->data);
		node->data = ft_strdup(env_var);
		if (node->data == NULL)
			return (-1);
	}
	return (0);
}

static int	set_env_var(
	const char *env_var,
	t_list *env_list,
	t_list *export_list
)
{
	t_node	*node;

	node = ft_list_find(env_list, (void *)env_var, is_key_exist);
	if (node == NULL)
	{
		if (add_node(env_list, export_list, env_var) < 0)
			return (1);
	}
	else
	{
		if (update(env_var, node, export_list) < 0)
			return (1);
	}
	return (0);
}

int	ft_export(t_command *cmd, t_list *env_list, t_list *export_list)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	if (cmd->argv[1] == NULL)
		return (print_export_list(export_list));
	while (cmd->argv[i] != NULL)
	{
		if (is_underscore_var(cmd->argv[i]) == 1)
		{
			i++;
			continue ;
		}
		if (handle_key_validation(cmd->argv[i]) == 1)
		{
			exit_status = 1;
			i++;
			continue ;
		}
		if (set_env_var(cmd->argv[i], env_list, export_list) < 0)
			return (1);
		i++;
	}
	return (exit_status);
}
