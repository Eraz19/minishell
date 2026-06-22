#ifndef HOOKS_TYPE_H
# define HOOKS_TYPE_H

# include "error.h"
# include "parser_stack_type.h"
# include <stddef.h>

typedef t_error	(*t_reduce_hook)(t_parser_stack_item *rhs, size_t len, void *ctx);

#endif
