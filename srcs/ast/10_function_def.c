#include "ast.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

void	ast_function_def_init(t_ast_function_def *function_def)
{
	assert(function_def != NULL);
	token_init(&function_def->name);
	function_def->body = NULL;
	ast_redir_list_init(&function_def->redirs);
}

void	ast_function_def_free(t_ast_function_def *function_def)
{
	assert(function_def != NULL);
	token_free(&function_def->name);
	if (function_def->body)
	{
		ast_command_free(function_def->body);
		free(function_def->body);
		function_def->body = NULL;
	}
	ast_redir_list_free(&function_def->redirs);
}
