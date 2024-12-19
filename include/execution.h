/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:46:08 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/19 09:21:12 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <sys/stat.h> 

typedef struct s_shell	t_shell;

//---------------------------------||EXECUTION||------------------------------//

void	execute_ast(t_shell *shell, t_ast *ast);
char	*find_command_path(t_shell *shell, char *command);
void	execute_command(t_shell *shell, t_token token);
int		check_ambigous_redir(t_shell *shell, t_redirect *redirect, int *fd);

//---------------------------------||  UTILS  ||------------------------------//

void	redirect_fd(int from_fd, int to_fd);
void	wait_update(t_shell *shell, pid_t pid);

//---------------------------------||  ERROR  ||------------------------------//

void	free_all(t_shell *shell);
int		open_error(t_shell *shell, char *path, int *fd, char *message);
void	exec_error(t_shell *shell, char *command_path, char *ms1, char *ms2);
int		check_error(char *command);
int		is_recursive(t_ast *ast);

#endif