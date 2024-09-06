#include "../include/minishell.h"

int main(int ac, char **av, char **envp)
{
	t_shell	shell;
	// char *input;

	// while (1) {
	// 	input = readline(PROMPT);
	// 	if (!input) {
	// 		printf("exit\n");
	// 		break;
	// 	}

	// 	if (*input) {
	// 		add_history(input);
	// 	}

	// 	printf("You entered: %s\n", input);
	// 	free(input);
	// }

	int i = 0;
	while (envp[i])
	{
		printf("env %d: %s\n", i, envp[i]);
		++i;
	}
	return (0);
}
