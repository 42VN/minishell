/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:49:27 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/25 23:13:43 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

static int	export_is_valid(char *str)
{
	if (*str == '\0' || *str == '=' || ft_isdigit(*str))
		return (0);
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}


/**
 * Function for <export> stadalone command.
 */
static int export_standalone(char **envp)
{
	int		i;
	char	**sorted_envp;
	char	*equal;

	i = 0;
	sorted_envp = env_dup_sorted(envp);
	if (!sorted_envp)
		return (1);
	while (sorted_envp[i])
	{
		if (sorted_envp[i][0] != '\0')
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			equal = ft_strchr(sorted_envp[i], '=');
			if (equal)
			{
				write(STDOUT_FILENO, sorted_envp[i], (equal - sorted_envp[i]) + 1);
				printf("\"%s\"\n", equal + 1);
			}
			else
				printf("%s\n", sorted_envp[i]);
		}
		++i;
	}
	return (ft_multi_free_null_ret(&sorted_envp, 0));
}

static int	export_variable(t_shell *shell, char *arg)
{
	char	*equal;
	char	*key;
	char	*value_str;
	
	if (!export_is_valid(arg))
		return (1);
	equal = ft_strchr(arg, '=');
	if (!equal)
	{
		key = arg;
		env_unset(shell, key);
		return (0);
	}
	key = ft_substr(arg, 0, (equal - arg)); 
	*equal = '\0';
	equal++;
	value_str = equal;
	env_unset(shell, key);
	env_set(shell, key, value_str);
	free(key);
	return (0);
}

int	ft_builtin_export(t_shell *shell, char **split_cmd)
{
	int		i;
	char	*equal;
	char	*key;
	
	i = 1;
	if (!split_cmd[1])
		return (export_standalone(shell->envp));
	while (split_cmd[i])
	{
		equal = ft_strchr(&split_cmd[i], '=');
		key = ft_substr(split_cmd[i], 0, equal - split_cmd[i]);
		if (!key)
			return (ft_error_ret("ft_builtin_export: malloc", shell, ERR_MALLOC, 1));
		equal = NULL;
		if (export_variable(shell, split_cmd[i]) == 1)
		{
			ft_printf_fd(2, "minishell: export: `%s': not a valid identifier\n", split_cmd[1]);
			return (1);
		}
		ft_free_null(&key);
		++i;
	}
	return (0);
}

int	ft_builtin_unset(t_shell *shell, char **split_cmd)
{
	int		i;
	char	*equal;
	char	*key;

	i = 1;
	if (!split_cmd[1])
		return (ft_error_ret(
			"ft_builtin_unset: Invalid argument",
			shell, ERR_MALLOC, 1));
	while (split_cmd[i])
	{
		equal = ft_strchr(split_cmd, '=');
		key = ft_substr(split_cmd[i], 0, equal - split_cmd[i]);
		if (!key)
			return (ft_error_ret("ft_builtin_unset: malloc", shell, ERR_MALLOC, 1));
		equal = NULL;
		env_unset(shell, key);
		ft_free_null(&key);
		++i;
	}
	return (0);
}
 
int	builtin_env(t_shell *shell, t_builtin_type type, char **split_cmd)
{
	char	*key;
	
	if (!shell || !split_cmd || !split_cmd[0])
	{
		ft_putstr_fd("minishell: builtin_env: Invalid parameter(s)\n", 2);
		return (1);
	}
	if (type == BI_ENV)
	{
		if (!env_get(shell->envp, "PATH", 1))
		{
			ft_putstr_fd("minishell: env: No such file or directory\n", 2);
			return (127);
		}
		env_print(shell->envp);
		return (0);
	}
	else if (type == BI_EXPORT)
		ft_builtin_export(shell, split_cmd);
	else if (type == BI_UNSET)
		ft_builtin_unset(shell, split_cmd);
}
