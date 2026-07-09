#include <unistd.h>
#include "alias.h"
#include "reader_.h"
#include "scanner_.h"

static t_error	scanner_stdin_input(t_string *res)
{
	t_error	err;

	string_init(res, 0, NULL, 0);
	if (!string_read_all(res, STDIN_FILENO))
		return (err = reader_read_error("standard input"),
			string_free(res), err);
	return (error(ERR_NO));
}

static t_error	scanner_dup_command_input(
					t_scanner *scanner,
					t_lexer_input_stack_item *item)
{
	if (!string_init(&item->str, 0, scanner->source, -1))
		return (scanner->err = error_sys());
	if (!string_append_n(&item->str, "\n", 1))
	{
		scanner->err = error_sys();
		return (string_free(&item->str), scanner->err);
	}
	return (scanner->err);
}

t_error	scanner_read_input(t_scanner *scanner) 
{
	t_lexer_input_stack_item	*item;

	scanner->err = lexer_input_stack_item_init(&item);
	if (scanner->err.type)
		return (scanner->err);
	if (scanner->mode == INPUT_MODE_FILE)
		scanner->err = reader_file_input(&item->str, scanner->source);
	else if (scanner->mode == INPUT_MODE_STRING)
	{
		if (scanner_dup_command_input(scanner, item).type)
			return (lexer_input_stack_item_free(&item), scanner->err);
	}
	else if (scanner->mode == INPUT_MODE_STDIN_PIPE)
		scanner->err = scanner_stdin_input(&item->str);
	else if (scanner->mode == INPUT_MODE_STDIN_TTY)
		scanner->err = reader_new_input(&item->str); 
	if (scanner->err.type || item->str.len < 2)
		return (lexer_input_stack_item_free(&item), scanner->err);
	scanner->err = lexer_input_stack_push(&scanner->lexer.input_stack, item);
	return (scanner->err);
}

t_error	scanner_alias_expand(t_scanner *scanner, t_token *token)
{
	t_lexer_input_stack_item	*item;

	scanner->err = lexer_input_stack_item_init(&item);
	if (scanner->err.type)
		return (scanner->err);
	scanner->err = alias_expand_token(&item->str, &token->value);
	if (scanner->err.type || item->str.len < 2)
		return (lexer_input_stack_item_free(&item), scanner->err);
	scanner->err = lexer_input_stack_push(&scanner->lexer.input_stack, item);
	if (scanner->err.type)
		return (lexer_input_stack_item_free(&item), scanner->err);
	token_free(token);
	if (lexer_get_next_token(&scanner->lexer, token,
			scanner_lexer_rules(scanner)).type)
		return (scanner->err = scanner->lexer.err);
	return (scanner->err);
}
