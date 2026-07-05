#include "functions.h"
#include "converter_priv.h"

void	function_init(t_function *function)
{
	ast_command_init(&function->body);
	ast_redir_list_init(&function->redirs);
}

void	function_free(t_function *function)
{
	ast_command_free(&function->body);
	ast_redir_list_free(&function->redirs);
}

void	function_free_void(void *function)
{
	function_free(function);
}

void	functions_init(t_functions *functions)
{
	hashmap_init(functions, 0, function_free_void);
}

void	functions_free(t_functions *functions)
{
	hashmap_free(functions);
}
