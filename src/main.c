/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:53:50 by ktieu             #+#    #+#             */
/*   Updated: 2024/09/18 18:08:43 by ktieu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell(t_shell *shell)
{
	char	*input;

	while (!shell->aborted)
	{
		input = ft_prompt(PROMPT);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
		{
			// printf("Input: [%s]\n", input);
			tokenize(shell, input);
			ft_token_print(shell);
			// shell->ast = build_ast(shell->tokens->array);
			// print_ast(shell->ast);
			// execute_ast(shell, shell->ast);
			ft_token_free(shell);
		}
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		free(input);
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
