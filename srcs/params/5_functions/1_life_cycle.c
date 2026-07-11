#include "functions.h"
#include <stdlib.h>

void	function_init(t_function *function)
{
	ast_command_init(&function->body);
	ast_redir_list_init(&function->redirs);
	function->active_count = 0;
	function->pending_free = false;
}

void	function_free(t_function **function)
{
	if (function == NULL || *function == NULL)
		return ;
	ast_command_free(&(*function)->body);
	ast_redir_list_free(&(*function)->redirs);
	(*function)->active_count = 0;
	(*function)->pending_free = false;
	free(*function);
	*function = NULL;
}

static void	function_free_void(void *function)
{
	t_function	*func;

	func = (t_function *)function;
	function_free(&func);
}

void	functions_init(t_functions *functions)
{
	hashmap_init(functions, 0, NULL);
}

void	functions_free(t_functions *functions)
{
	functions->del_value = function_free_void;
	hashmap_free(functions);
}
