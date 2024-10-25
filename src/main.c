/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktieu <ktieu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:53:50 by ktieu             #+#    #+#             */
/*   Updated: 2024/10/25 22:23:03 by ktieu            ###   ########.fr       */
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
		
		if (*input)
		{
			
			if (tokenize(shell, input))
			{
				ft_token_print(shell);
				// shell->ast = build_ast(shell->tokens->array);
				shell->tokens->array[0].split_cmd = ft_split(shell->tokens->array[0].cmd, ' ');
				if (ft_strnstr(input, "export", ft_strlen("export"))
					|| ft_strnstr(input, "env", ft_strlen("env"))
					|| ft_strnstr(input, "unset", ft_strlen("export"))
				)
				{
					t_builtin_type type = get_builtin(shell->tokens->array[0].split_cmd[0]);
					builtin_env(shell, type, shell->tokens->array[0].split_cmd);
				}
				ft_multi_free_null(&shell->tokens->array[0].split_cmd);
				// shell->ast = build_ast(shell->tokens->array);
				// printf("\n----PRINT AST-------\n");
				// print_ast(shell->ast);
				// execute_ast(shell, shell->ast);
			}
	
			
			ft_token_free(shell);
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
