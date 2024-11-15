/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:53:50 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/15 11:28:02 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_signaled(t_shell *shell)
{
	if (shell->exitcode - 128 == SIGQUIT)
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	else if (shell->exitcode - 128 == SIGSEGV)
		write(STDERR_FILENO, "Segmentation fault (core dumped)\n", 33);
}

static void ft_print_split_cmd(t_shell *shell)
{
	size_t	i = 0;
	size_t	j = 0;
	while (i <= shell->tokens->cur_pos)
	{
		j = 0;
		printf("\n------------------------\n");
		printf("Split cmd\n");
		printf("------------------------\n");
		while (shell->tokens->array[i].split_cmd[j])
		{
			printf("[%s] ", shell->tokens->array[i].split_cmd[j]);
			++j;
		}
		printf("\n");
		++i;
	}
	printf("\n");
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
			if (tokenize(shell, input))
			{
				// ft_token_print(shell);
				// ft_print_split_cmd(shell);
				// expansion(shell);
				// ft_token_print(shell);
				read_heredoc(shell, shell->tokens->array, get_tokens_size(shell->tokens->array));
				shell->ast = build_ast(shell->tokens->array);//, 0);
				execute_ast(shell, shell->ast);
			}
			print_signaled(shell);
			if (shell->ast)
				ast_cleanup(&shell->ast);
			ft_token_free(shell);
		}
		print_signaled(shell);
		free(input);
		input = NULL;
	}
	rl_clear_history();
	return ;
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	shell_init(&shell, envp);
	if (!set_signals(&shell, PARENT))	//811
		return (shell.exitcode);
	minishell(&shell);
	shell_cleanup(&shell);
	return (0);
}
