#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#define PROMPT "minishell> "

int main(int ac, char **av, char **envp)
{
	char *input;

	while (1) {
		input = readline(PROMPT);
		if (!input) {
			printf("exit\n");
			break;
		}

		if (*input) {
			add_history(input);
		}

		printf("You entered: %s\n", input);
		free(input);
	}

	return (0);
}