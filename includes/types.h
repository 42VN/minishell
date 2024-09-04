/**
 * Structure for program
 * @param ac Argument count
 * @param av Argument vector
 * @param envp Environment varibale path vector
 */
typedef struct s_prog
{
	int		ac;
	char	**av;
	char	**envp;
}	t_prog;

/**
 * Structure for signal handler
 */
typedef struct s_sighandler
{
	
}	t_sighandler;