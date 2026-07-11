#include "functions_priv.h"
#include <stdlib.h>

static inline void	function_take_body(t_function *dst, t_ast_function_def *src)
{
	dst->body = *src->body;
	free(src->body);
	src->body = NULL;
}

static inline void	function_take_redirs(t_function *dst, t_ast_function_def *src)
{
	dst->redirs = src->redirs;
	ast_redir_list_init(&src->redirs);
}

t_error	function_set(t_functions *functions, t_ast_function_def *function_def)
{
	t_function	*function;
	t_error		err;
	
	function_unset(functions, function_def->name.value.data);
	function = malloc(sizeof(*function));
	if (function == NULL)
		return (error_sys());
	function_init(function);
	function_take_body(function, function_def);
	function_take_redirs(function, function_def);
	if (!hashmap_put(functions, function_def->name.value.data, function))
		return (err = error_sys(), function_free(&function), err);
	return (error(ERR_NO));
}
