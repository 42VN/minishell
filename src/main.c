/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:53:50 by ktieu             #+#    #+#             */
/*   Updated: 2024/11/07 11:56:32 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		if (ft_strcmp(input, ""))
			add_history(input);
		if (*input)
		{
			
			if (tokenize(shell, input))
			{
				// ft_token_print(shell);
				read_heredoc(shell->tokens->array, get_tokens_size(shell->tokens->array));
				shell->ast = build_ast(shell->tokens->array);//, 0);
				execute_ast(shell, shell->ast);
			}
			if (shell->ast)
				ast_cleanup(&shell->ast);
			ft_token_free(shell);
		}
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
	minishell(&shell);
	shell_cleanup(&shell);
	return (0);
}
