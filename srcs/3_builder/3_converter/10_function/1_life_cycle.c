#include "converter_priv.h"
#include <stdlib.h>

void	ast_function_def_init(t_ast_function_def *function_def)
{
	function_def->name = NULL;
	function_def->body = NULL;
	ast_redir_list_init(&function_def->redirs);
}

void	ast_function_def_free(t_ast_function_def *function_def)
{
	function_def->name = NULL;
	if (function_def->body)
	{
		ast_command_free(function_def->body);
		free(function_def->body);
		function_def->body = NULL;
	}
	ast_redir_list_free(&function_def->redirs);
}
