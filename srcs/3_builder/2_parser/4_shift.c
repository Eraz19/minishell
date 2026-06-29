#include "parser_priv.h"
#include "cst.h"
# include <assert.h>	// DEBUG

t_error	parser_shift(t_parser *parser, size_t lr_state_id)
{
	t_parser_stack_item	item;
	t_error				err;

	assert(parser != NULL);
	err = parser_read_heredoc(parser);
	if (err.type)
		return (err);
	item.symbol = parser->lookahead_symbol;
	item.lr_state_id = lr_state_id;
	item.tokens_start_id = parser->lookahead_id;
	item.tokens_count = 1;
	err = cst_node_new(&item, NULL, 0, RULE_NONE);
	if (err.type != ERR_NO)
		return (err);
	if (!vector_push(&parser->stack, &item))
	{
		err = error_sys();
		cst_node_free(&item.cst_node);
		return (parser_internal_error(err));
	}
	return (parser_read_next_symbol(parser));
}
