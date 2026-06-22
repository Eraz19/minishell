#include "parser.h"
#include "parser_priv.h"
#include "qualifiers.h"
#include "qualifiers_priv.h"
# include <stdio.h>	// DEBUG

static t_error	parser_push_initial_state(t_parser *parser)
{
	t_parser_stack_item	item;

	item.symbol = SYM_error;
	item.lr_state_id = 0;
	item.tokens_start_id = 0;
	item.tokens_count = 0;
	item.cst_node = NULL;
	if (!vector_push(&parser->stack, &item))
		return (parser_internal_error());
	return (error(ERR_NO));
}

static inline t_error	parser_prepare_to_build_cst(t_parser *parser)
{
	t_error		err;

	parser_reset(parser);
	err = parser_push_initial_state(parser);
	if (err.type == ERR_NO)
		err = parser_read_next_symbol(parser);
	return (err);
}

static inline t_error	parser_store_cst(t_parser *parser)
{
	t_parser_stack_item	*main_item;

	main_item = parser_stack_top(&parser->stack);
	printf("[PARSER] ACCEPT root=%s state=%zu token_start=%zu token_count=%zu\n",
		symbol_to_string(main_item->symbol),
		main_item->lr_state_id,
		main_item->tokens_start_id,
		main_item->tokens_count);
	parser->cst = main_item->cst_node;
	main_item->cst_node = NULL;
	return (error(ERR_NO));
}

t_error	parser_build_cst(t_parser *parser, t_lr_machine *machine)
{
	size_t		lr_state_id;
	t_token		*token;
	t_action	action;
	t_error		err;

	err = parser_prepare_to_build_cst(parser);
	lr_state_id = 0;
	while (err.type == ERR_NO)
	{
		lr_state_id = parser_stack_top(&parser->stack)->lr_state_id;
		token = &((t_token *)parser->tokens.data)[parser->lookahead_id];
		err = parser_qualify_symbol(parser, lr_state_id, token);
		if (err.type != ERR_NO)
			return (err);
		action = machine->actions[lr_state_id][parser->lookahead_symbol];
		printf("[PARSER] ACTION state=%zu lookahead=%s action=%s payload=%zu\n",
			lr_state_id,
			symbol_to_string(parser->lookahead_symbol),
			action_type_to_string(action.type),
			action.payload);
		if (action.type == ACTION_ERROR)
			return (parser_invalid_syntax());
		else if (action.type == ACTION_ACCEPT)
			return (parser_store_cst(parser));
		else if (action.type == ACTION_SHIFT)
			err = parser_shift(parser, action.payload);
		else if (action.type == ACTION_REDUCE)
			err = parser_reduce(parser, machine, action.payload);
	}
	return (err);
}

bool	parser_can_next_token_be_a_cmd_name_or_word(t_parser *parser)
{
	size_t		lr_state_id;
	t_qualifier	qualifier;

	lr_state_id = parser_stack_top(&parser->stack)->lr_state_id;
	qualifier = parser->qualifiers[lr_state_id];
	return (qualifier == qualify_7a || qualifier == qualify_7b);
}
