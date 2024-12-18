/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:32:25 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/18 17:10:37 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct s_shell	t_shell;

void	builtin_echo(t_shell *shell, char **token);
void	builtin_cd(t_shell *shell, char **token);
void	builtin_pwd(t_shell *shell);
void	builtin_export(t_shell *shell, char **token);
void	builtin_unset(t_shell *shell, char **token);
void	builtin_env(t_shell *shell, char **token);
void	builtin_exit(t_shell *shell, char **token);

//---------------------------------||  UTILS  ||------------------------------//

int		builtin_error(t_shell *shell, char *s, int error_num);
int		update_pwd(t_shell *shell);
void	export_standalone_print(char *env_var);
int		inaccessible_parent_dir(t_shell *shell, char *path);

#endif
