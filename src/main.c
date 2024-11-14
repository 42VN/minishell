/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:53:50 by ktieu             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/08 18:15:39 by ktieu            ###   ########.fr       */
=======
/*   Updated: 2024/11/11 16:45:15 by ktieu            ###   ########.fr       */
>>>>>>> dev_kha
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
<<<<<<< HEAD
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
=======
>>>>>>> dev_kha
		if (ft_strcmp(input, ""))
			add_history(input);
		if (*input)
		{
			if (tokenize(shell, input))
			{
<<<<<<< HEAD
				ft_token_print(shell);
=======
				// ft_token_print(shell);
				ft_print_split_cmd(shell);
>>>>>>> dev_kha
				// expansion(shell);
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
