/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:41:23 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/18 16:06:22 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

struct s_shell;
typedef struct s_shell t_shell;

char	*env_get(char **envp, char *key, int include_key);
char	**env_dup(char **envp);
char	**env_dup_sorted(char **envp);
void	env_sort(char **envp);
void	env_print(char **envp);
int		env_set(t_shell *shell, char *key, char *value);
void	env_unset(t_shell *shell, char *key);

#endif