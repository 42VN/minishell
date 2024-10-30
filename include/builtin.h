/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:32:25 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/30 21:44:34 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct s_shell	t_shell;

typedef enum e_builtin_type
{
	BI_UNDEFINED = 0,
	BI_CD = 1,
	BI_PWD = 2,
	BI_ECHO = 3,
	BI_EXIT = 4,
	BI_ENV = 5,
	BI_EXPORT = 6,
	BI_UNSET = 7
}	t_builtin_type;

t_builtin_type	get_builtin(char *str);
int				builtin_env(
					t_shell *shell,
					t_builtin_type type,
					char **split_cmd);

int	execute_builtin(t_shell *shell, char **token);
int	builtin_echo(char **token);
int	builtin_cd(t_shell *shell, char **token);
int	builtin_pwd(t_shell *shell);
// int	builtin_export(t_shell *shell, char **token);
// int	builtin_unset(t_shell *shell, char **token);
// int	builtin_env(t_shell *shell, char **token);
int	builtin_exit(t_shell *shell, char **token);

//---------------------------------||  UTILS  ||------------------------------//

int		builtin_error(char *s, int error_num);
char	*get_envp_variable(char **envp, char *key);
int		update_pwd(t_shell *shell);

#endif
