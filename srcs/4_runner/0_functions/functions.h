#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "ast_type.h"

typedef struct s_function
{
	t_ast_command		body;	// owned
	t_ast_redir_list	redirs;	// owned
}	t_function;

// key = function name
// value = function body (t_function)
typedef t_hashmap	t_functions;

void	functions_init(t_functions *functions);
void	functions_free(t_functions *functions);

void	function_init(t_function *function);
void	function_free(t_function *function);
void	function_free_void(void *function);

// TODO
t_error	function_set(t_functions *functions, t_ast_function_def *function_def);

// TODO
t_error	function_unset(t_functions *functions, const char *name);

#endif
