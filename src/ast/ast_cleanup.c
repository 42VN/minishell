#include "minishell.h"

void ast_cleanup(t_ast **ast)
{
	if (!ast || !*ast)
		return;
	if ((*ast)->left)
		ast_cleanup(&((*ast)->left));
	if ((*ast)->right)
		ast_cleanup(&((*ast)->right));
	free(*ast);
	*ast = NULL;
}
