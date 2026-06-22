#ifndef HOOKS_H
# define HOOKS_H

# include "error.h"
# include "parser_stack_type.h"

// Triggered on SYM_io_here reduction
t_error	hook_3(t_parser_stack_item *rhs, size_t len, void *ctx);

// Triggered by hook_fname()
t_error	hook_9_increment(t_parser_stack_item *rhs, size_t len, void *ctx);

// Triggered on SYM_function_body reduction
t_error	hook_9_decrement(t_parser_stack_item *rhs, size_t len, void *ctx);

/*
* Triggered on SYM_fname reduction
* Rule 9 starts here
* Although function_body is parsed later, only '(' ')' and linebreak can appear
* before it, so disabling assignment and expansion now is safe.
*/
t_error	hook_fname(t_parser_stack_item *rhs, size_t len, void *ctx);

#endif
