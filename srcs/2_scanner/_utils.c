#include <stdlib.h>
#include "alias.h"
#include "reader_.h"
#include "scanner_.h"

static t_error	scanner_dup_command_input(
	t_scanner *state,
	t_input_parser_stack_item *item)
{
	char	*command;

	command = str_dup(state->source);
	if (command == NULL)
		state->err = error_sys();
	item->str = str_join(command, "\n");
	if (item->str == NULL)
		state->err = error_sys();
	return (free(command), state->err);
}

t_error	scanner_read_input(t_scanner *state) 
{
	t_input_parser_stack_item	*item;

	state->err = input_parser_stack_item_init(&item);
	if (state->err.type)
		return (state->err);
	if (state->mode == SCAN_FILE)
		state->err = reader_file_input(&item->str, state->source);
	else if (state->mode == SCAN_STRING)
	{
		if (scanner_dup_command_input(state, item).type)
			return (input_parser_stack_item_free(&item), state->err);
	}
	else if (state->mode == SCAN_STDIN)
		state->err = reader_new_input(&item->str); 
	if (state->err.type || item->str == NULL)
		return (input_parser_stack_item_free(&item), state->err);
	return (state->err = input_stack_push(&state->lexer.input_stack, item));
}

t_error	scanner_alias_expand(t_scanner *state, t_token *token)
{
	t_input_parser_stack_item	*item;

	state->err = input_parser_stack_item_init(&item);
	if (state->err.type)
		return (state->err);
	state->err = alias_expand_token(&item->str, &token->value);
	if (state->err.type || item->str == NULL)
		return (input_parser_stack_item_free(&item), state->err);
	input_stack_push(&state->lexer.input_stack, item);
	token_free(token);
	if (lexer_next_token(&state->lexer, token).type)
		return (state->err = state->lexer.err);
	return (state->err);
}
