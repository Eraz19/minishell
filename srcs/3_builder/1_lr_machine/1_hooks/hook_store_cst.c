#include "parser_type.h"
#include "parser.h"

t_error	hook_store_cst(
	t_parser *parser,
	t_parser_stack_item *rhs,
	size_t len,
	t_parser_stack_item *lhs)
{
	(void)rhs;
	(void)len;
	return (parser_store_cst(parser, lhs));
}
