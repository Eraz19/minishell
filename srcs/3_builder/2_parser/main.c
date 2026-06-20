#include "parser_priv.h"

static t_error	parser_push_initial_state(t_parser *parser)
{
	t_stack_item	item;

	item.symbol = SYM_error;
	item.lr_state_id = 0;
	item.tokens_start_id = 0;
	item.tokens_count = 0;
	item.cst_node = NULL;
	if (!vector_push(&parser->stack, &item))
		return (parser_internal_error());
	return (error(ERR_NO));
}

# include <stdio.h>
static inline t_error	parser_store_cst(t_parser *parser)
{
	t_stack_item	*main_item;

	main_item = parser_stack_top(&parser->stack);
	parser->cst = main_item->cst_node;
	parser_stack_free(&parser->stack);
	printf("[PARSER] ACCEPT root=%s state=%zu token_start=%zu token_count=%zu\n",
		symbol_to_string(main_item->symbol),
		main_item->lr_state_id,
		main_item->tokens_start_id,
		main_item->tokens_count);
	return (error(ERR_NO));
}

# include <stdio.h>
t_error	parser_build_cst(t_parser *parser, t_lr_machine *machine)
{
	size_t		state_id;
	t_action	*action;
	t_error		err;

	parser_free(parser);
	parser_init(parser);
	state_id = 0;
	err = parser_push_initial_state(parser);
	if (err.type != ERR_NO)
		return (err);
	err = parser_read_next_symbol(parser);
	while (err.type == ERR_NO)
	{
		state_id = parser_stack_top(&parser->stack)->lr_state_id;
		action = &machine->actions[state_id][parser->lookahead_symbol];
		printf("[PARSER] ACTION state=%zu lookahead=%s action=%s payload=%zu\n",
			state_id,
			symbol_to_string(parser->lookahead_symbol),
			action_type_to_string(action->type),
			action->payload);
		if (action->type == ACTION_ERROR)
			return (parser_invalid_syntax());
		else if (action->type == ACTION_ACCEPT)
			return (parser_store_cst(parser));
		else if (action->type == ACTION_SHIFT)
			err = parser_shift(parser, action->payload);
		else if (action->type == ACTION_REDUCE)
			err = parser_reduce(parser, machine, action->payload);
	}
	return (err);
}
