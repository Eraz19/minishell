#include <unistd.h>
#include "alias.h"
#include "reader_.h"
#include "scanner_.h"

static t_error	scanner_stdin_input(t_string *res)
{
	t_error	err;

	string_init(res, 0, NULL, 0);
	if (!string_read_all(res, STDIN_FILENO))
		return (err = error_sys(), string_free(res), err);
	return (error(ERR_NO));
}

static t_error	scanner_dup_command_input(
					t_scanner *state,
					t_lexer_input_stack_item *item)
{
	if (!string_init(&item->str, 0, state->source, -1))
		return (state->err = error_sys());
	if (!string_append_n(&item->str, "\n", 1))
		return (state->err = error_sys(), string_free(&item->str), state->err);
	return (state->err);
}

t_error	scanner_read_input(t_scanner *state) 
{
	t_lexer_input_stack_item	*item;

	state->err = lexer_input_stack_item_init(&item);
	if (state->err.type)
		return (state->err);
	if (state->mode == SCAN_FILE)
		state->err = reader_file_input(&item->str, state->source);
	else if (state->mode == SCAN_STRING)
	{
		if (scanner_dup_command_input(state, item).type)
			return (lexer_input_stack_item_free(&item), state->err);
	}
	else if (state->mode == SCAN_STDIN_PIPE)
		state->err = scanner_stdin_input(&item->str);
	else if (state->mode == SCAN_STDIN_TTY)
		state->err = reader_new_input(&item->str); 
	if (state->err.type || item->str.len < 2)
		return (lexer_input_stack_item_free(&item), state->err);
	state->err = lexer_input_stack_push(&state->lexer.input_stack, item);
	return (state->err);
}

t_error	scanner_alias_expand(t_scanner *state, t_token *token)
{
	t_lexer_input_stack_item	*item;

	state->err = lexer_input_stack_item_init(&item);
	if (state->err.type)
		return (state->err);
	state->err = alias_expand_token(&item->str, &token->value);
	if (state->err.type || item->str.len < 2)
		return (lexer_input_stack_item_free(&item), state->err);
	lexer_input_stack_push(&state->lexer.input_stack, item);
	token_free(token);
	if (lexer_get_next_token(&state->lexer, token,
			scanner_lexer_rules(state)).type)
		return (state->err = state->lexer.err);
	return (state->err);
}
