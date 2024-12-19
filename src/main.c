/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:53:50 by ktieu             #+#    #+#             */
/*   Updated: 2024/12/19 11:16:19 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	loop_cleanup(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->ast)
		ast_cleanup(&shell->ast);
	if (shell->tokens)
		ft_token_free(shell);
	shell->err_type = ERR_NONE;
}

static void	process_input(t_shell *shell, char **input, int size)
{
	if (!*input || !**input)
		return ;
	if (tokenize(shell, *input))
	{
		free(*input);
		*input = NULL;
		size = get_tokens_size(shell->tokens->array);
		if (!size)
			return ;
		if (!expansion(shell)
			|| read_heredoc(shell, shell->tokens->array, size) == EXIT_FAILURE
			|| shell->err_type == ERR_SYNTAX
			|| !expansion_heredoc(shell)
			|| wildcard(shell->tokens->array, size) == EXIT_FAILURE
			|| remove_quotes(shell->tokens->array, size) == EXIT_FAILURE)
			return ;
		shell->ast = build_ast(shell->tokens->array);
		if (!shell->ast)
			return ;
		execute_ast(shell, shell->ast);
		print_fault(shell);
	}
}

void	minishell(t_shell *shell)
{
	char	*input;

	while (!shell->aborted)
	{
		if (init_signals() == EXIT_FAILURE)
			return ;
		input = readline(PROMPT);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strcmp(input, ""))
		{
			add_history(input);
			process_input(shell, &input, 0);
			loop_cleanup(shell);
		}
		free(input);
	}
	rl_clear_history();
	return ;
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
	shell_init(&shell, envp);
	minishell(&shell);
	shell_cleanup(&shell);
	exit (shell.exitcode);
}
