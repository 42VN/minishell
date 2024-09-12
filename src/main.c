#include "../include/minishell.h"

static void minishell(t_shell *shell)
{
	char	*input;

	while (!shell->aborted)
	{
		input = ft_prompt(PROMPT);
		if (!input)
		{
			printf("exit\n");
			break;
		}
		printf("You entered: %s\n", input);
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break;
		}
		free(input);
	}
	return;
}


int main(int ac, char **av, char **envp)
{
	t_shell	shell;
	
	shell_init(&shell, envp);
	// minishell(&shell);
    if (ac > 1)
    {
		tokenize(&shell, av);
		int i = 0;
		ft_token_print(&shell);
		ft_token_free(&shell);	
	}
	shell_cleanup(&shell);
	return (0);
}
