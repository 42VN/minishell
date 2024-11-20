/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:46:08 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/19 22:09:45 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_shell	t_shell;

//---------------------------------||EXECUTION||------------------------------//

void	execute_ast(t_shell *shell, t_ast *ast);
char	*find_command_path(char **envp, char *command);
void	execute_command(t_shell *shell, t_token token);

//---------------------------------||  UTILS  ||------------------------------//

void	redirect_fd(int from_fd, int to_fd);
void	ft_free_triptr(char ***str);
int		update_status(t_shell *shell, int new_status); //0111
void	wait_update(t_shell *shell, pid_t pid);
void	print_fault(t_shell *shell);

//---------------------------------||  ERROR  ||------------------------------//

void	free_all(t_shell *shell);
void	open_error(t_shell *shell, char *path, int *fd);
void	exec_error(t_shell *shell, char *command_path);

#endif