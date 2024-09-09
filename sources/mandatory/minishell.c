/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:01:17 by hitran            #+#    #+#             */
/*   Updated: 2024/09/05 14:45:25 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int g_errno = 0;

static  void	exit_error(t_msh *msh, char *str, int n)
{
	if (msh)
		free (msh);
	ft_printf_fd(2, "msh: %s\n", str);
	exit(n);
}

static char	*find_envp_path(char **envp)
{
	while (*envp && !ft_strnstr(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		return (ft_strdup("./"));
	return (ft_substr(*envp, 5, ft_strlen(*envp) - 5));
}

static int	get_shell_level(char **envp)
{
	while (*envp && !ft_strnstr(*envp, "SHLVL=", 6))
		envp++;
	return (ft_atoi(ft_strchr(*envp, '=') + 1));
}

static void	init_msh(t_msh *msh, char **envp)
{
	msh->envp = ft_matrix_dup(envp, ft_matrixlen(envp));
	if (!msh->envp)
		exit_error(msh, "Envp duplication failed", 1);
	msh->path = find_envp_path(envp);
	msh->level = get_shell_level(envp) + 1;
}

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_errno = 1;
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

static void	child_handler(int signal)
{
	if (signal == SIGINT)
		g_errno = 130;
	else if (signal == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		g_errno = 131;
	}
	return ;
}

void	wait_signal(int i)
{
	struct sigaction	sa;

	if (i)
		sa.sa_handler = &signal_handler;
	else
		sa.sa_handler = &child_handler;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}

void	receive_args(t_msh *msh)
{
	char	*read_line;

	while (1)
	{
		read_line = readline("minishell>");
		if (!read_line)
			exit_error(msh, "exit", g_errno);
		if (ft_is_all_white_spaces(read_line) == -1 || read_line[0] == '\0')
		{
			free(read_line);
			printf(" ");
		}
		else
		{
			add_history(read_line);
			if (tokenize(msh, &msh->cmd, read_line) && msh->flags->quote != 0)
			{
				if (check_nonpipables(msh->cmd, str_noquotes(msh->cmd->cmd)))
					execute_nonpipe(msh->cmd, str_noquotes(msh->cmd->cmd));
				else
					execute_cmd(&(msh->cmd), init_pipes(), 1);
			}
		}
	}
}

void minishell(char **envp)
{
	t_msh *msh;

	msh = ft_calloc(sizeof(t_msh), 1);
	if (!msh)
		exit_error(msh, "Memory allocation failed", 1);
	g_errno = 0;
	init_msh(msh, envp);
	wait_signal(1);
	receive_args(msh);
	exit (EXIT_SUCCESS);
}
