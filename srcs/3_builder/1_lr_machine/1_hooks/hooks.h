#ifndef HOOKS_H
# define HOOKS_H

# include "error.h"
# include "parser_item_stack_type.h"

// Triggered on SYM_io_here reduction
t_error	hook_3(
	t_parser *parser,
	t_parser_item *rhs,
	size_t len,
	t_parser_item *lhs);

// Triggered by hook_fname()
t_error	hook_9_increment(
	t_parser *parser,
	t_parser_item *rhs,
	size_t len,
	t_parser_item *lhs);

// Triggered on SYM_function_body reduction
t_error	hook_9_decrement(
	t_parser *parser,
	t_parser_item *rhs,
	size_t len,
	t_parser_item *lhs);

/*
* Triggered on SYM_fname reduction
* Rule 9 starts here
* Although function_body is parsed later, only '(' ')' and linebreak can appear
* before it, so disabling assignment and expansion now is safe.
*/
t_error	hook_fname(
	t_parser *parser,
	t_parser_item *rhs,
	size_t len,
	t_parser_item *lhs);

t_error	hook_store_cst(
	t_parser *parser,
	t_parser_item *rhs,
	size_t len,
	t_parser_item *lhs);

t_error	hook_cmd_sub(
		t_parser *parser,
		t_parser_item *rhs,
		size_t len,
		t_parser_item *lhs);

#endif
