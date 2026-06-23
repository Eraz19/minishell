#ifndef HOOKS_TYPE_H
# define HOOKS_TYPE_H

# include "error.h"
# include <stddef.h>

typedef struct s_parser_stack_item	t_parser_stack_item;
typedef struct s_parser				t_parser;
typedef struct s_cst_node			t_cst_node;

typedef t_error	(*t_reduce_hook)(
	t_parser *parser,
	t_parser_stack_item *rhs,
	size_t len,
	t_parser_stack_item *lhs);

#endif
