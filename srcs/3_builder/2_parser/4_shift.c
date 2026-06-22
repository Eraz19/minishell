#include "parser_priv.h"

# include <stdio.h>
t_error	parser_shift(t_parser *parser, size_t lr_state_id)
{
	t_parser_stack_item	item;
	t_error			err;

	item.symbol = parser->lookahead_symbol;
	item.lr_state_id = lr_state_id;
	item.tokens_start_id = parser->lookahead_id;
	item.tokens_count = 1;
	err = parser_cst_node_new(&item, NULL, 0, &item.cst_node);
	if (err.type != ERR_NO)
		return (err);
	// printf("[PARSER] SHIFT symbol=%s to_state=%zu token_start=%zu token_count=%zu\n",
	// 	symbol_to_string(item.symbol),
	// 	item.lr_state_id,
	// 	item.tokens_start_id,
	// 	item.tokens_count);
	if (!vector_push(&parser->stack, &item))
	{
		parser_cst_node_free(&item.cst_node);
		return (parser_internal_error());
	}
	return (parser_read_next_symbol(parser));
}
