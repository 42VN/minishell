/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:42:06 by hitran            #+#    #+#             */
/*   Updated: 2024/10/30 21:28:29 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_home(t_shell *shell)
{
	char	*path;

	path = get_envp_variable(shell->envp, "HOME");
	if (!path)
		return (cd_error("minishell: cd: HOME not set\n", 1));
	if (chdir(path))
	{
		perror("minishell: cd");
		return (EXIT_FAILURE);
	}
	return (update_pwd(shell));
}

int	cd_tilde(t_shell *shell, char *token)
{
	char	*home;
	char	*path;

	home = get_envp_variable(shell->envp, "HOME");
	if (!home)
		return (cd_error("minishell: cd: HOME not set\n", 1));
	path = ft_strjoin(home, (token + 1));
	if (!path)
		return (cd_error("minishell: cd: memory allocation failed\n", 1));
	if (chdir(path))
	{
		perror("minishell: cd");
		free(path);
		return (EXIT_FAILURE);
	}
	free(path);
	return (update_pwd(shell));
}

int	cd_oldpwd(t_shell *shell)
{
	char	*path;

	path = get_envp_variable(shell->envp, "OLDPWD");
	if (!path)
		return (cd_error("minishell: cd: OLDPWD not set\n", 1));
	if (chdir(path))
	{
		perror("minishell: cd");
		update_status(1);
		return (EXIT_FAILURE);
	}
	printf("%s\n", path);
	return (update_pwd(shell));

}

int	cd_path(t_shell *shell, char *path)
{
	if (chdir(path))
	{
		perror("minishell: cd");
		update_status(1);
		return (EXIT_FAILURE);
	}
	return (update_pwd(shell));
}

int	builtin_cd(t_shell *shell, char **token)
{
	// printf("home = %s\n", get_envp_variable(shell->envp, "HOME"));
	if (token[1] && token[2])
		return (cd_error("minishell: cd: too many arguments\n", 2));
	else if (!token[1] || token[1][0] == '\0' || !ft_strcmp(token[1], "~"))
		return (cd_home(shell));
	else if (token[1][0] == '~')
		return (cd_tilde(shell, token[1]));
	else if (!ft_strcmp(token[1], "-"))
		return (cd_oldpwd(shell));
	else
		return (cd_path(shell, token[1]));
}
