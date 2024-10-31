/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:53:50 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/31 14:15:41 by ktieu            ###   ########.fr       */
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
				// shell->ast = build_ast(shell->tokens->array);
				shell->ast = build_ast(shell->tokens->array);
				// printf("\n----PRINT AST-------\n");
				// print_ast(shell->ast);
				execute_ast(shell, shell->ast);
			}
			ft_token_free(shell);
		}
		free(input);
		input = NULL;
	}
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
