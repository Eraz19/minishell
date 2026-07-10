#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "ast.h"

// type

typedef struct s_function
{
	t_ast_command		body;
	t_ast_redir_list	redirs;
	t_token_pool		token_pool;
	size_t				active_count;
	bool				pending_free;
}	t_function;

// key = function name
// value = function body (t_function)
typedef t_hashmap	t_functions;

// Life cycle

void	functions_init(t_functions *functions);
void	functions_free(t_functions *functions);

void	function_init(t_function *function);
void	function_free(t_function *function);
void	function_free_void(void *function);

// ops

// TODO (si existe => pending_free = true puis remplacer)
t_error	function_set(t_functions *functions, const t_ast_function_def *function_def);

// TODO (error if pending_free = true, else increment active_count)
// (pas de const car le pointeur doit pouvoir être rendu à function_stop qui MAY free la fonction)
t_error	function_get(const t_functions *functions, const char *name, t_function **out_function);

// TODO (si active_count == 0 => free, else set pending_free = true)
t_error	function_unset(t_functions *functions, const char *name);

// TODO (decrement active_count puis free si active_count == 0 && pending_free == true)
void	function_stop(t_function *function);

#endif
