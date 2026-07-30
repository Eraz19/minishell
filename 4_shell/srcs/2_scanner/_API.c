#include "heredoc.h"
#include "scanner.h"
#include "scanner_priv.h"

t_error	scanner_get_next_token(t_scanner *scanner, t_token *out, bool ps2)
{
	if (update_input(scanner, out, ps2).type)
		return (scanner->err);
	if (lexer_get_next_token(&scanner->lexer, out).type)
		return (scanner->err = requalify_scanner_error(scanner->lexer.err));
	if (out->type == TOKEN_TOKEN)
		return (expand_alias(scanner, out));
	return (scanner->err);
}

t_error	scanner_read_heredoc(t_scanner *scanner, t_string *out, t_token *delim, bool strip)
{
	heredoc_read_body(&scanner->lexer, out, delim, strip);
	return (requalify_scanner_error(scanner->err = scanner->lexer.err));
}

t_error	scanner_bind_input(t_scanner *scanner, const char *cmd_string)
{
	t_lexer_input_stack	*input_stack;
	t_lexer_input_stack	*parent_input_stack;

	lexer_clear(&scanner->lexer);
	scanner->source = cmd_string;
	if (scanner->mode == SCAN_MODE_CMD_SUB)
	{
		input_stack = &scanner->lexer.input_stack;
		parent_input_stack = &scanner->parent_scanner->lexer.input_stack;
		scanner->err = lexer_input_stack_dup(input_stack, parent_input_stack);
	}
	return (scanner->err);
}
