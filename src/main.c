/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:53:50 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/22 20:02:31 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void ft_print_split_cmd(t_shell *shell)
// {
// 	size_t	i = 0;
// 	size_t	j = 0;
// 	while (i <= shell->tokens->cur_pos)
// 	{
// 		j = 0;
// 		printf("\n------------------------\n");
// 		printf("Split cmd\n");
// 		printf("------------------------\n");
// 		if (shell->tokens->array[i].split_cmd)
// 		{
// 			while (shell->tokens->array[i].split_cmd[j])
// 			{
// 				printf("[%s] ", shell->tokens->array[i].split_cmd[j]);
// 				++j;
// 			}
// 		}
// 		printf("\n");
// 		++i;
// 	}
// 	printf("\n");
// }

static void	free_input(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->ast)
		ast_cleanup(&shell->ast);
	ft_token_free(shell);
}

static void	process_input(t_shell *shell, char *input)
{
	int		size;

	if (tokenize(shell, input))
	{
		ft_token_print(shell);
		size = get_tokens_size(shell->tokens->array);
		if (!size)
			return ;
		if (!read_heredoc(shell, shell->tokens->array, size))
			return ;
		expansion(shell);
		// ft_token_print(shell);
		if (wildcard(shell->tokens->array, size) == EXIT_FAILURE)
			return ;
		shell->ast = build_ast(shell->tokens->array);
		if (!shell->ast)
			return ;
		execute_ast(shell, shell->ast);
	}
}

static void	minishell(t_shell *shell)
{
	char	*input;

	while (!shell->aborted)
	{
		input = readline(PROMPT);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strcmp(input, ""))
			add_history(input);
		if (*input)
		{
			process_input(shell, input);
			free_input(shell);
		}
		free(input);
		input = NULL;
	}
	rl_clear_history();
	return ;
}

#include <termios.h>

static int	disable_echoctl(void)
{
	struct termios	term;

	if (isatty(STDIN_FILENO) == 1)
	{
		if (tcgetattr(STDIN_FILENO, &term) < 0)
		{
			perror("minishell: tcgetattr");
			return (-1);
		}
		term.c_lflag &= ~ECHOCTL;
		if (tcsetattr(STDIN_FILENO, TCSANOW, &term) < 0)
		{
			perror("minishell: tcsetattr");
			return (-1);
		}
	}
	return (0);
}

static int	enable_echoctl(void)
{
	struct termios	term;

	if (isatty(STDIN_FILENO) == 1)
	{
		if (tcgetattr(STDIN_FILENO, &term) < 0)
		{
			perror("minishell: tcgetattr");
			return (-1);
		}
		term.c_lflag |= ECHOCTL;
		if (tcsetattr(STDIN_FILENO, TCSANOW, &term) < 0)
		{
			perror("minishell: tcsetattr");
			return (-1);
		}
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	if (ac != 1)
	{
		ft_putendl_fd("Error: invalid number of arguments!\n", 2);
		exit (EXIT_FAILURE);
	}
	(void)av;
	if (disable_echoctl() < 0)
		return (EXIT_FAILURE);
	shell_init(&shell, envp);
	if (!start_signal(&shell, PARENT))
		return (shell.exitcode);
	minishell(&shell);
	shell_cleanup(&shell);
	if (enable_echoctl() < 0)
		return (EXIT_FAILURE);
	exit (EXIT_SUCCESS);
}
