#ifndef HOOKS_H
# define HOOKS_H

# include "error.h"
# include "parser_stack_type.h"

t_error	hook_3(t_parser_stack_item *rhs, size_t len, void *ctx);
t_error	hook_9_increment(t_parser_stack_item *rhs, size_t len, void *ctx);
t_error	hook_9_decrement(t_parser_stack_item *rhs, size_t len, void *ctx);

#endif
