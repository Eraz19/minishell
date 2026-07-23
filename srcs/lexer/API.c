#include <stdlib.h>
#include "ast.h"
#include "lexer.h"
#include "scanner.h"

void	lexer_pop_last_input_stack_on_end(t_lexer *lexer)
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
	if (lexer->scanner->mode == SCAN_MODE_CMD_SUB && !lexer->emited_token)
	{
		lexer->emited_token = true;
		return (lexer->err = lexer_consume(lexer, TOKEN_DOLPAREN, 2));
	}
	lexer->emited_token = false;
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

static t_error	pop_alias_stack_input(
			t_lexer *lexer,
			t_token *token,
			t_lexer_rules rules)
{
	if (token->type == TOKEN_EOF && lexer->input_stack.len > 1)
	{
		lexer_pop_last_input_stack_on_end(lexer);
		if (lexer->err.type)
			return (lexer->err);
		return (token_free(token), lexer_get_next_token(lexer, token, rules));
	}
	return (lexer->err);
}

t_error	lexer_get_next_token(
			t_lexer *lexer,
			t_token *token,
			t_lexer_rules rules)
{
	lexer->rules = rules;
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
	return (pop_alias_stack_input(lexer, token, rules));
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
	context_stack_init(context_out);
	ast_vector_init(ast_vec_out);
	lexer->err = lexer_input_stack_get_last(&lexer->input_stack, &lexer->input);
	if (lexer->err.type)
		return (context_stack_free(context_out),
			ast_vector_free(ast_vec_out), lexer->err);
	lexer->err = context_stack_item_init(&item, CONTEXT_NONE);
	if (lexer->err.type)
		return (context_stack_free(context_out),
			ast_vector_free(ast_vec_out), lexer->err);
	token_init(&token);
	lexer->token = &token;
	args.context = CONTEXT_NONE;
	args.opening_len = 0;
	args.closing_len = 0;
	args.stack_item = item;
	if (lexer_context_scan(lexer, args).type)
		return (free(item), token_free(&token),
			context_stack_free(context_out), ast_vector_free(ast_vec_out),
			lexer->err);
	vector_take(context_out, &token.contexts);
	vector_take(ast_vec_out, &token.ast_vector);
	return (free(item), token_free(&token), lexer->err);
}

t_error	lexer_remove_escaped_newlines(
			t_lexer *lexer,
			t_string *word,
			t_lexer_context_args args)
{
	t_token					token;
	t_context_stack_item	*item;
	t_error					err;

	err = lexer_push_input(lexer, word);
	if (err.type == ERR_NO)
		err = lexer_input_stack_get_last(&lexer->input_stack, &lexer->input);
	if (err.type)
		return (err);
	err = context_stack_item_init(&item, CONTEXT_NONE);
	if (err.type)
		return (err);
	token_init(&token);
	lexer->token = &token;
	args.context = CONTEXT_NONE;
	args.opening_len = 0;
	args.closing_len = 0;
	args.stack_item = item;
	err = lexer_context_scan(lexer, args);
	if (err.type == ERR_NO)
		string_take_string(word, &token.value);
	return (free(item), token_free(&token), err);
}
