#include "minishell.h"

void ast_cleanup(t_ast *ast)
{
	if (!ast)
		return;
	ast_cleanup(ast->left);
	ast_cleanup(ast->right);
	free(ast);
	ast = NULL;
}
