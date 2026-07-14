#ifndef PARSER_ITEM_STACK_TYPE_H
# define PARSER_ITEM_STACK_TYPE_H

# include "libft.h"
# include "cst_type.h"
# include "symbols_type.h"
# include <stddef.h>

typedef struct s_parser_item
{
	t_symbol	symbol;
	size_t		lr_state_id;
	size_t		tokens_start_id;
	size_t		tokens_count;
	t_cst_node	*cst_node;
}	t_parser_item;

// vector of t_parser_item
typedef t_vector	t_parser_item_stack;

#endif
