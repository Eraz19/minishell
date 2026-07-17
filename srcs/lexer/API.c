#include <stdlib.h>
#include "lexer.h"

static void	lexer_input_EOF(t_lexer *lexer)
{
	lexer->input = NULL;
	lexer_input_stack_pop(&lexer->input_stack);
	if (lexer->rules.on_input_end != NULL)
		lexer->rules.on_input_end(lexer);
}

static t_error	lexer_scan_token(t_lexer *lexer, t_token *token)
{
	t_context	context;

	token_init(token);
	lexer->token = token;
	if (lexer->input_stack.len == 1)
		lexer->token->index.start = (ssize_t)lexer->input->i;
	else
		lexer->token->index.start = lexer->last_index.start;
	while (!lexer->emited_token)
	{
		if (lexer->rules.recognize(lexer, &context).type)
			return (lexer->err);
	}
	return (lexer->err);
}

t_error	lexer_get_next_token(
			t_lexer *lexer,
			t_token *token,
			t_lexer_rules rules)
{
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
	if (lexer_scan_token(lexer, token).type)
		return (lexer->err);
	if (token->type == TOKEN_EOF && lexer->input_stack.len > 0)
	{
		lexer_input_EOF(lexer);
		if (lexer->err.type || lexer->input_stack.len == 0)
			return (lexer->err);
		return (token_free(token), lexer_get_next_token(lexer, token, rules));
	}
	return (lexer->err);
}

t_error	lexer_track_context(
	t_lexer *lexer,
	t_context_stack *context_out,
	t_ast_vector *ast_vec_out,
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
	vector_take(context_out, &token.contexts);
	vector_take(ast_vec_out, &token.ast_vector);
	//lexer->err = context_stack_dup(context_out, &token.contexts);
	return (free(item), token_free(&token), lexer->err);
}

t_error	lexer_remove_escaped_newlines(
	t_string *word,
	t_lexer_context_args args)
{
	t_token					token;
	t_lexer					lexer;
	t_error					err;
	t_context_stack_item	*item;

	lexer_init(&lexer);
	err = lexer_push_input(&lexer, word);
	if (!err.type)
		err = lexer_input_stack_get_last(&lexer.input_stack, &lexer.input);
	if (err.type)
		return (lexer_free(&lexer), err);
	err = context_stack_item_init(&item, CONTEXT_NONE);
	if (err.type)
		return (lexer_free(&lexer), err);
	token_init(&token);
	lexer.token = &token;
	args.context = CONTEXT_NONE;
	args.opening_len = 0;
	args.closing_len = 0;
	args.stack_item = item;
	err = lexer_context_scan(&lexer, args);
	if (!err.type && !string_dup(word, &token.value))
		err = error_sys();
	return (free(item), token_free(&token), lexer_free(&lexer), err);
}
