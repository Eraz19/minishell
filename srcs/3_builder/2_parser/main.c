#include "parser.h"
#include "parser_priv.h"
#include "parser_item_stack.h"
#include "parser_here_stack.h"
#include "qualifiers.h"
#include "cst.h"
#ifdef DEBUG_PARSING
# include "debug.h"		// DEBUG
# include "logs.h"		// DEBUG
# include <stdio.h>		// DEBUG
#endif
# include <assert.h>	// DEBUG

static inline t_error	parser_push_initial_state(t_parser *parser)
{
	t_parser_item	item;

	item.symbol = SYM_error;
	item.lr_state_id = 0;
	item.tokens_start_id = 0;
	item.tokens_count = 0;
	item.cst_node = NULL;
	if (!vector_push(&parser->item_stack, &item))
		return (parser_internal_error(error_sys()));
	return (error(ERR_NO));
}

static inline t_error	parser_prepare_to_build_cst(t_parser *parser)
{
	t_error	err;

	parser_item_stack_clear(&parser->item_stack);
	parser_here_stack_clear(&parser->here_stack);
	err = parser_push_initial_state(parser);
	if (err.type == ERR_NO && parser->lookahead_raw_symbol == SYM_NONE)
		err = parser_read_next_symbol(parser);
	cst_node_free(&parser->cst);
	parser->cst = NULL;
	parser->function_body_depth = 0;
	parser->assignment_disabled = false;
	parser->expansion_disabled = false;
	return (err);
}

t_error	parser_store_cst(t_parser *parser, t_parser_item *main_item)
{
	assert(parser != NULL);
	assert(main_item != NULL);
#ifdef DEBUG_PARSING
	fprintf(stderr, "[PARSER] ACCEPT =======> %s%s%s (token_start=%zu token_count=%zu)\n",
		GREEN, symbol_to_string(main_item->symbol), NC,
		main_item->tokens_start_id,
		main_item->tokens_count);
#endif
	parser->cst = main_item->cst_node;
	main_item->cst_node = NULL;
	if (parser->lookahead_raw_symbol == SYM_NEWLINE)
		return (parser_read_heredoc(parser));
	return (error(ERR_NO));
}

static inline t_error	parser_accept(t_parser *parser)
{
	t_parser_item	*main_item;
	bool			is_EOF;
	t_error			err;

	is_EOF = parser->lookahead_raw_symbol == SYM_EOF;
	parser->lookahead_raw_symbol = SYM_NONE;
	parser->lookahead_symbol = SYM_NONE;
	main_item = parser_item_stack_top(&parser->item_stack);
	err = parser_store_cst(parser, main_item);
	if (err.type == ERR_NO && is_EOF)
		return (error(ERR_EOF));
	return (err);
}

t_error	parser_build_cst(t_parser *parser, const t_lr_machine *machine)
{
	size_t			lr_state_id;
	const t_token	*token;
	t_action		action;
	t_error			err;

	assert(parser != NULL);
	assert(machine != NULL);
	err = parser_prepare_to_build_cst(parser);
	while (err.type == ERR_NO && parser->cst == NULL)
	{
		lr_state_id = parser_item_stack_top(&parser->item_stack)->lr_state_id;
		token = parser_get_token(parser, parser->lookahead_id);
		err = parser_qualify_symbol(parser, lr_state_id, token);
		if (err.type != ERR_NO)
			return (err);
		action = machine->actions[lr_state_id][parser->lookahead_symbol];
		if (action.type == ACTION_SHIFT)
			err = parser_shift(parser, action.payload);
		else if (action.type == ACTION_REDUCE)
			err = parser_reduce(parser, machine, action.payload);
		if (action.type == ACTION_ACCEPT)
			return (parser_accept(parser));
		else if (action.type == ACTION_ERROR)
			return (parser_handle_syntax_errors(parser, machine));
	}
	return (err);
}

t_error	parser_handle_syntax_errors(t_parser *parser, const t_lr_machine *machine)
{
	size_t			lr_state_id;
	const t_token	*token;
	t_action		action;
	t_error			err;

	if (parser->search_cmd_sub_end != true
		|| parser->lookahead_raw_symbol != SYM_RPARENTHESIS)
		return (parser_invalid_syntax());
	parser->lookahead_raw_symbol = SYM_EOF;
	parser->lookahead_symbol = SYM_EOF;
	token = parser_get_token(parser, parser->lookahead_id);
	parser->cmd_sub_end_index = token->index.end;
	err.type = ERR_NO;
	while (err.type == ERR_NO && parser->cst == NULL)
	{
		lr_state_id = parser_item_stack_top(&parser->item_stack)->lr_state_id;
		action = machine->actions[lr_state_id][parser->lookahead_symbol];
		if (action.type == ACTION_REDUCE)
			err = parser_reduce(parser, machine, action.payload);
		if (action.type == ACTION_ACCEPT)
			return (parser_accept(parser));
		else if (action.type == ACTION_ERROR || action.type == ACTION_SHIFT)
			return (parser_invalid_syntax());
	}
	return (err);
}
