/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:42:06 by hitran            #+#    #+#             */
/*   Updated: 2024/10/28 23:30:39 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_error(char *s, int cd_erroror_num)
{
	write(STDERR_FILENO, s, ft_strlen(s));
	update_status(cd_erroror_num);
	return (EXIT_FAILURE);
}

char	*get_envp_variable(char **envp, char *key)
{
	size_t	len;

	len = ft_strlen(key);
	while (*envp)
	{
		if (!ft_strncmp(*envp, key, len) && envp[len] == '=')
			return (*envp + len + 1);
		envp++;
	}
	return (NULL);
}

static void add_envp_variable(t_shell *shell, const char *new)
{
	int		len;
	char	**new_envp;

	len = 0;
	while (shell->envp && shell->envp[len])
		len++;
	new_envp = malloc((len + 2) * sizeof(char *));
	if (!new_envp)
		return ;
	new_envp[len] = strdup(new);
	new_envp[len + 1] = NULL;
	while (--len >= 0)
	{
		new_envp[len] = strdup(shell->envp[len]);
		free (shell->envp[len]);
	}
	free(shell->envp);
	shell->envp = new_envp;
}

static void	update_envp(t_shell *shell, char *key, char *value)
{
	char	*temp;
	char	**cur;

	temp = ft_strjoin(key, value);
	cur = shell->envp;
	while (*cur)
	{
		if (!ft_strncmp(*cur, key, ft_strlen(key)))
		{
			free (*cur);
			*cur = ft_strdup(temp);
			free (temp);
			return ;
		}
		cur++;
	}
	add_envp_variable(shell, temp);
	free(temp);
	temp = NULL;
}

int	update_pwd(t_shell *shell)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (cd_error("minishell: getcwd failed\n", 1));
	free(shell->old_pwd);
	shell->old_pwd = shell->cwd;
	shell->cwd = ft_strdup(new_pwd);
	free (new_pwd);
	if (!shell->cwd)
		return (cd_error("minishell: strdup failed\n", 1));
	update_envp(shell, "OLDPWD=", shell->old_pwd);
	update_envp(shell, "PWD=", shell->cwd);
	return (EXIT_SUCCESS);
}
