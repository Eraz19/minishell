#include <stdlib.h>
#include "lexer.h"

static t_error	lexer_input_EOF(t_lexer *state)
{
	state->input = NULL;
	state->err = lexer_input_stack_pop(&state->input_stack);
	if (state->err.type)
		return (state->err);
	if (state->rules.on_input_end != NULL)
		return (state->rules.on_input_end(state));
	return (state->err);
}

t_error	lexer_get_next_token(
			t_lexer *state,
			t_token *token,
			t_lexer_rules rules)
{
	t_context	context;

	state->rules = rules;
	state->emited_token = false;
	if (state->input == NULL)
	{
		state->err = lexer_input_stack_get_last(&state->input_stack, &state->input);
		if (state->err.type)
			return (state->err);
	}
	token_init(token);
	state->token = token;
	if (state->input_stack.len == 1)
		state->token->index.start = (ssize_t)state->input->i;
	while (!state->emited_token)
	{
		if (state->rules.recognize(state, &context).type)
			return (state->err);
	}
	if (token->type == TOKEN_EOF && state->input_stack.len > 0)
		lexer_input_EOF(state);
	return (state->err);
}

t_error	lexer_track_context(
	t_lexer *state,
	t_context_stack *out,
	t_lexer_context_args args)
{
	t_token					token;
	t_context_stack_item	*item;

	state->rules = (t_lexer_rules){0};
	state->err = lexer_input_stack_get_last(&state->input_stack, &state->input);
	if (state->err.type)
		return (state->err);
	state->err = context_stack_item_init(&item, CONTEXT_NONE);
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
