/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:39:55 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/22 11:46:58 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_is_valid(char *str)
{
	if (*str == '\0' || *str == '=' || ft_isdigit(*str))
	{
		return (0);
	}
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
		{
			return (0);
		}
		str++;
	}
	return (1);
}

/**
 * Function for <export> stadalone command.
 */
static int	export_standalone(char **envp)
{
	int		i;
	char	**sorted_envp;
	// char	*equal;

	i = 0;
	sorted_envp = env_dup_sorted(envp);
	if (!sorted_envp)
		return (1);
	while (sorted_envp[i])
	{
		if (sorted_envp[i][0] != '\0')
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			export_standalone_print(sorted_envp[i]);
		}
		++i;
	}
	return (ft_multi_free_null_ret(&sorted_envp, 0));
}

static int	export_variable(t_shell *shell, char *arg)
{
	char	*equal;
	char	*key;

	if (!export_is_valid(arg))
		return (1);
	equal = ft_strchr(arg, '=');
	key = ft_substr(arg, 0, (equal - arg));
	if (equal)
	{
		equal++;
		if (ft_isspace(*equal))
			equal = "";
		if ((*equal == '\'' || *equal=='\"')
			&& (*(equal + 1) == '\'' || *(equal + 1)=='\"'))
		{
			equal = "";
		}
		env_unset(shell, key);
	}
	env_set(shell, key, equal);
	free(key);
	return (0);
}

static int	ft_builtin_export(t_shell *shell, char **split_cmd)
{
	int		i;
	char	*equal;
	char	*key;

	i = 1;
	if (!split_cmd[1])
		return (export_standalone(shell->envp));
	while (split_cmd[i])
	{
		equal = ft_strchr(split_cmd[i], '=');
		key = ft_substr(split_cmd[i], 0, equal - split_cmd[i]);
		if (!key)
			return (ft_error_ret("ft_builtin_export: malloc",
					shell, ERR_MALLOC, 1));
		equal = NULL;
		if (export_variable(shell, split_cmd[i]) == 1)
		{
			ft_printf_fd(2, "minishell: export: `%s': not a valid identifier\n",
				split_cmd[1]);
			return (1);
		}
		ft_free_null(&key);
		++i;
	}
	return (0);
}

void	builtin_export(t_shell *shell, char **split_cmd)
{
	if (!shell || !split_cmd || !split_cmd[0])
	{
		ft_putstr_fd("minishell: builtin_env: Invalid parameter(s)\n", 2);
		update_status (shell, 1);
		return ;
	}
	update_status(shell, ft_builtin_export(shell, split_cmd));
}