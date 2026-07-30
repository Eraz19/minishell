#include "parser_type.h"
#include "parser.h"

t_error	hook_store_cst(
	t_parser *parser,
	t_parser_item *rhs,
	size_t len,
	t_parser_item *lhs)
{
	(void)rhs;
	(void)len;
	if (parser->search_cmd_sub_end == false || parser->lookahead_raw_symbol == SYM_RPARENTHESIS)
		return (parser_store_cst(parser, lhs));
	return (error(ERR_NO));
}
