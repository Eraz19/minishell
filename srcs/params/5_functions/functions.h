#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "ast.h"

// type

typedef struct s_function
{
	t_ast_command		body;
	t_ast_redir_list	redirs;
	size_t				active_count;
	bool				pending_free;
}	t_function;

// key = function name
// value = function body (t_function)
typedef t_hashmap	t_functions;

// Life cycle

void	functions_init(t_functions *functions);
void	functions_clear(t_functions *functions);
void	functions_free(t_functions *functions);

// ops

t_error	function_set(t_functions *functions, t_ast_function_def *function_def);

t_error	function_get(t_functions *functions, const char *name, t_function **out);

void	function_unset(t_functions *functions, const char *name);

void	function_stop(t_function **function);

#endif
