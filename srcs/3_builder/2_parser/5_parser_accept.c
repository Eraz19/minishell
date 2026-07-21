#include "parser.h"
#include "parser_priv.h"
#include "parser_item_stack.h"

# include "logs.h"
t_error	parser_accept(t_parser *parser)
{
	t_parser_item	*main_item;
	bool			is_EOF;
	t_error			err;

	fprintf(stderr, YELLOW "[%s()] is accepting\n" NC, __func__);
	is_EOF = parser->lookahead_raw_symbol == SYM_EOF;
	parser->lookahead_raw_symbol = SYM_NONE;
	parser->lookahead_symbol = SYM_NONE;
	main_item = parser_item_stack_top(&parser->item_stack);
	err = parser_store_cst(parser, main_item);
	if (err.type == ERR_NO && is_EOF)
		return (error(ERR_EOF));
	return (err);
}
