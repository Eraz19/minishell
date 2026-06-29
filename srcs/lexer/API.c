#include <stdlib.h>
#include "lexer.h"

t_error	lexer_track_context(t_lexer *state, t_context_stack *out,
		t_lexer_context_args args)
{
	t_token						token;
	t_context_parser_stack_item	*item;

	state->rules = (t_lexer_rules){0};
	state->err = input_stack_get_last(&state->input_stack, &state->input);
	if (state->err.type)
		return (state->err);
	state->err = context_parser_stack_item_init(&item, CONTEXT_NONE);
	if (state->err.type)
		return (state->err);
	token_init(&token);
	state->token = &token;
	args.context = CONTEXT_NONE;
	args.opening_len = 0;
	args.closing_len = 0;
	args.stack_item = item;
	if (lexer_context_scan(state, args).type)
		return (free(item), token_free(&token), state->err);
	state->err = context_stack_dup(out, &token.contexts);
	return (free(item), token_free(&token), state->err);
}
