#include "parser_priv.h"
#include "scanner.h"

# include <stdio.h>
static inline t_error	parser_trigger_heredoc_read(t_parser *parser)
{
	if (parser->lookahead_raw_symbol != SYM_NEWLINE)
		return (error(ERR_NO));
	if (!parser->must_read_heredoc)
		return (error(ERR_NO));
	parser->must_read_heredoc = false;
	printf("----------\n");
	printf ("[PARSER] [%s] scanner_heredoc_read()\n", __func__);
	printf("----------\n");
	return (scanner_heredoc_read());
}

# include <stdio.h>
t_error	parser_shift(t_parser *parser, size_t lr_state_id)
{
	t_parser_stack_item	item;
	t_error			err;

	err = parser_trigger_heredoc_read(parser);
	if (err.type)
		return (err);
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
