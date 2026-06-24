#include "converter_priv.h"
#include <stdlib.h>

void	ast_function_def_init(t_ast_function_def *function_def)
{
	buff_init(&function_def->name, 0, NULL, -1);
	function_def->body = NULL;
	ast_redir_list_init(&function_def->redirs);
}

void	ast_function_def_free(t_ast_function_def *function_def)
{
	buff_free(&function_def->name);
	if (function_def->body)
	{
		ast_command_free(function_def->body);
		free(function_def->body);
		function_def->body = NULL;
	}
	ast_redir_list_free(&function_def->redirs);
}
