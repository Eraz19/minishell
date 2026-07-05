#include <stdlib.h>
#include "lexer.h"

static t_error	lexer_input_EOF(t_lexer *lexer)
{
	lexer->input = NULL;
	lexer->err = lexer_input_stack_pop(&lexer->input_stack);
	if (lexer->err.type)
		return (lexer->err);
	if (lexer->rules.on_input_end != NULL)
		return (lexer->rules.on_input_end(lexer));
	return (lexer->err);
}

t_error	lexer_get_next_token(
			t_lexer *lexer,
			t_token *token,
			t_lexer_rules rules)
{
	t_context	context;

	lexer->rules = rules;
	lexer->emited_token = false;
	if (lexer->input == NULL)
	{
		lexer->err = lexer_input_stack_get_last(
						&lexer->input_stack,
						&lexer->input);
		if (lexer->err.type)
			return (lexer->err);
	}
	token_init(token);
	lexer->token = token;
	if (lexer->input_stack.len == 1)
		lexer->token->index.start = (ssize_t)lexer->input->i;
	while (!lexer->emited_token)
	{
		if (lexer->rules.recognize(lexer, &context).type)
			return (lexer->err);
	}
	if (token->type == TOKEN_EOF && lexer->input_stack.len > 0)
		lexer_input_EOF(lexer);
	return (lexer->err);
}

t_error	lexer_track_context(
	t_lexer *lexer,
	t_context_stack *out,
	t_lexer_context_args args)
{
	t_token					token;
	t_context_stack_item	*item;

	lexer->rules = (t_lexer_rules){0};
	lexer->err = lexer_input_stack_get_last(&lexer->input_stack, &lexer->input);
	if (lexer->err.type)
		return (lexer->err);
	lexer->err = context_stack_item_init(&item, CONTEXT_NONE);
	if (lexer->err.type)
		return (lexer->err);
	token_init(&token);
	lexer->token = &token;
	args.context = CONTEXT_NONE;
	args.opening_len = 0;
	args.closing_len = 0;
	args.stack_item = item;
	if (lexer_context_scan(lexer, args).type)
		return (free(item), token_free(&token), lexer->err);
	lexer->err = context_stack_dup(out, &token.contexts);
	return (free(item), token_free(&token), lexer->err);
}
