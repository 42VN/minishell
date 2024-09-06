#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "../libft/libft.h"
#include "./types.h"

#define PROMPT "minishell> "

//----------------------------------------------------
// ENVP 
//-----------------------------------------------------

char	**envp_dup(char **envp);

//----------------------------------------------------
// SHELL 
//-----------------------------------------------------

int		shell_init(t_shell *shell, char **envp);
void	shell_cleanup(t_shell *shell);