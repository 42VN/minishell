/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:53:50 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/26 15:39:08 by ktieu            ###   ########.fr       */
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
}

static void	process_input(t_shell *shell, char **input)
{
	int		size;

	if (!*input || !**input)
		return ;
	if (tokenize(shell, *input))
	{
		free(*input);
		*input = NULL;
		size = get_tokens_size(shell->tokens->array);
		if (!size)
			return ;
		if (!read_heredoc(shell, shell->tokens->array, size))
			return ;
		if (wildcard(shell->tokens->array, size) == EXIT_FAILURE)
			return ;
		expansion(shell);
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
		//Snippet for testing
		if (isatty(fileno(stdin)))
			input = readline(PROMPT);
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			input = ft_strtrim(line, "\n");
			free(line);
		}
		char *temp = ft_strdup(input);
		free (input);
		input = temp;
		if (!input)
			break ;
		if (ft_strcmp(input, ""))
			add_history(input);
		if (*input)
		{
			process_input(shell, &input);
			loop_cleanup(shell);
		}
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
	if (!start_signal(&shell, PARENT))
		return (shell.exitcode);
	minishell(&shell);
	shell_cleanup(&shell);
	exit (shell.exitcode);
}
