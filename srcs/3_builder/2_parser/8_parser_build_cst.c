#include "parser.h"
#include "parser_priv.h"
#include "parser_item_stack.h"
#include "parser_here_stack.h"
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
		err = parser_read_next_symbol(parser, false);
	cst_node_free(&parser->cst);
	parser->cst = NULL;
	return (err);
}

static inline void	parser_build_cycle(t_parser *parser, size_t *lr_state_id)
{
	const t_token	*token;

	*lr_state_id = parser_item_stack_top(&parser->item_stack)->lr_state_id;
	parser->lookahead_symbol = parser->lookahead_raw_symbol;
	if (parser->lookahead_symbol != SYM_TOKEN)
		return ;
	if (parser->machine->qualifiers[*lr_state_id] == NULL)
		return ;
	token = parser_get_token(parser, parser->lookahead_id);
	parser->machine->qualifiers[*lr_state_id](token, &parser->lookahead_symbol);
}

static inline t_error	parser_try_continuation(
							t_parser *parser,
							size_t *lr_state_id)
{
	t_action	*action;
	size_t		i;

	if (parser->lookahead_symbol != SYM_EOF)
		return (parser_invalid_syntax());
	i = 0;
	while (i <= SYM_TERMINAL_MAX)
	{
		action = &parser->machine->actions[*lr_state_id][i];
		if (action->type != ACTION_ERROR)
			return (parser_read_next_symbol(parser, true));
		i++;
	}
	return (parser_invalid_syntax());
}

t_error	parser_build_cst(t_parser *parser)
{
	size_t			lr_state_id;
	t_action		action;
	t_error			err;

	assert(parser != NULL);
	err = parser_prepare_to_build_cst(parser);
	while (err.type == ERR_NO && parser->cst == NULL)
	{
		parser_build_cycle(parser, &lr_state_id);
		action = parser->machine->actions[lr_state_id][parser->lookahead_symbol];
		if (action.type == ACTION_SHIFT)
			err = parser_shift(parser, action.payload);
		else if (action.type == ACTION_REDUCE)
			err = parser_reduce(parser, action.payload);
		if (action.type == ACTION_ACCEPT)
			return (parser_accept(parser));
		else if (action.type == ACTION_ERROR)
		{
			err = parser_try_continuation(parser, &lr_state_id);
			if (err.type)
				return (err);
		}
	}
	return (err);
}
