#include "reader.h"
#include "scanner.h"
#include "scanner_priv.h"
#include "lexer_input_stack.h"

t_error	update_input_file(t_scanner *scanner, t_lexer_input_stack_item *out)
{
	scanner->err = reader_read_file(&out->str, scanner->source);
	if (scanner->err.type)
		return (scanner->err);
	if (!string_append_n(&out->str, "\n", 1))
		return (scanner->err = error_sys());
	return (scanner->err);
}

t_error	update_input_string(t_scanner *scanner, t_lexer_input_stack_item *out)
{
	if (!string_init(&out->str, 0, scanner->source, -1))
		return (scanner->err = error_sys());
	if (!string_append_n(&out->str, "\n", 1))
		return (scanner->err = error_sys());
	return (scanner->err);
}

t_error	update_input_stdin(t_scanner *scanner, t_lexer_input_stack_item *out)
{
	return (scanner->err = reader_read_PS1(&out->str));
}

t_error	update_input_dispatch(t_scanner *scanner) 
{
	t_lexer_input_stack_item	new_input;
	t_lexer_input_stack			*input_stack;

	lexer_input_stack_item_init(&new_input);
	if (scanner->mode == SCAN_MODE_FILE)
		update_input_file(scanner, &new_input);
	else if (scanner->mode == SCAN_MODE_STRING)
		update_input_string(scanner, &new_input);
	else if (scanner->mode == SCAN_MODE_STDIN)
		update_input_stdin(scanner, &new_input);
	if (scanner->err.type)
		return (lexer_input_stack_item_free(&new_input), scanner->err);
	input_stack = &scanner->lexer.input_stack;
	scanner->err = lexer_input_stack_push(input_stack, &new_input);
	return (scanner->err);
}

t_error	update_input(t_scanner *scanner, t_token *out, bool ps2)
{
	if (ps2)
	{
		read_and_propagate_PS2(scanner);
		return (scanner->err = scanner_requalify_error(scanner->err));
	}
	else if (scanner->lexer.input_stack.len == 0)
	{
		if (update_input_dispatch(scanner).type)
			return (scanner->err = scanner_requalify_error(scanner->err));
		if (scanner->lexer.input_stack.len == 0)
			return (token_init(out), out->type = TOKEN_EOF, scanner->err);
	}
	return (scanner->err);
}
