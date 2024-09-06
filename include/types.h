
typedef enum e_token_type
{
	COMMAND,
	PIPE,
	OR,
	AND,
	REDIRECT_IN_O,
	REDIRECT_OUT_O,
	REDIRECT_IN_A,
	REDIRECT_OUT_A,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*str;
}	t_token;



typedef struct s_shell
{
	char	**envp;
	char	*cwd;
}	t_shell;


typedef struct s_sighandler
{
	
}	t_sighandler;