/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:32:25 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/19 22:43:07 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct s_shell	t_shell;

int		builtin_echo(char **token);
int		builtin_cd(t_shell *shell, char **token);
int		builtin_pwd(t_shell *shell);
int		builtin_export(t_shell *shell, char **token);
int		builtin_unset(t_shell *shell, char **token);
int		builtin_env(t_shell *shell, char **token);
int		builtin_exit(t_shell *shell, char **token);

//---------------------------------||  UTILS  ||------------------------------//

int		builtin_error(t_shell *shell, char *s, int error_num);
int		update_pwd(t_shell *shell);
void	export_check_value(t_shell *shell, char **value_str);
void	export_standalone_print(char *env_var);

#endif
