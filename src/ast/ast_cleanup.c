#include "minishell.h"

void ast_cleanup(t_ast *ast)
{
	t_redirect *redirect;
	t_redirect *next;

	if (!ast)
		return;
	ast_cleanup(ast->left);
	ast_cleanup(ast->right);
	if (ast->token.cmd)
		free(ast->token.cmd);
	if (ast->token.split_cmd)
	{
		for (int i = 0; ast->token.split_cmd[i]; i++)
			free(ast->token.split_cmd[i]);
		free(ast->token.split_cmd);
	}
	redirect = ast->token.redirect;
	while (redirect)
	{
		next = redirect->next;
		if (redirect->path)
			free(redirect->path);
		free(redirect);
		redirect = next;
	}
	free(ast);
}	

// void tokens_cleanup(t_token *tokens)
// {
// 	int i = 0;
// 	t_redirect *redirect;
// 	t_redirect *next;

// 	if (!tokens)
// 		return;

// 	while (tokens[i].type || tokens[i].cmd)
// 	{
// 		if (tokens[i].cmd)
// 			free(tokens[i].cmd);
		
// 		if (tokens[i].split_cmd)
// 		{
// 			for (int j = 0; tokens[i].split_cmd[j]; j++)
// 				free(tokens[i].split_cmd[j]);
// 			free(tokens[i].split_cmd);
// 		}
// 		redirect = tokens[i].redirect;
// 		while (redirect)
// 		{
// 			next = redirect->next;
// 			if (redirect->path)
// 				free(redirect->path);
// 			free(redirect);
// 			redirect = next;
// 		}

// 		i++;
// 	}
// 	free(tokens);
// }

