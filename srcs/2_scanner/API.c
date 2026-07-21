#include "heredoc.h"
#include "scanner.h"
#include "scanner_.h"

t_error	scanner_get_next_token(t_scanner *scanner, t_token *token)
{
	t_lexer_rules	lexer_rules;

	if (scanner->lexer.input_stack.len == 0)
	{
		if (scanner_read_input(scanner).type)
			return (scanner->err = scanner_error_qualify(scanner->err, true));
		if (scanner->lexer.input_stack.len == 0)
			return (token_init(token), token->type = TOKEN_EOF, scanner->err);
	}
	lexer_rules = scanner_lexer_rules();
	if (lexer_get_next_token(&scanner->lexer, token, lexer_rules).type)
	{
		scanner->err = scanner_error_qualify(scanner->lexer.err, false);
		return (scanner->err);
	}
	if (token->type == TOKEN_TOKEN)
	{
		scanner_alias_expand(scanner, token);
		return (scanner->err = scanner_error_qualify(scanner->err, false));
	}
	return (scanner->err);
}

t_error	scanner_read_heredoc(
			t_scanner *scanner,
			t_string *out,
			t_token *delim,
			bool strip)
{
	t_heredoc_read_args	args;
	t_string			delim_exp;

	scanner->err = heredoc_expand_delim(&delim_exp, delim);
	if (scanner->err.type)
		return (scanner->err = scanner_error_qualify(scanner->err, false));
	prepare_heredoc_read_args(scanner, &args, strip, &delim_exp);
	scanner->err = heredoc_read_body_from_input(out, &args);
	scanner->err = scanner_error_qualify(scanner->err, false);
	return (string_free(&delim_exp), scanner->err);
}

void	scanner_set_input(t_scanner *scanner, const t_string *cmd_string)
{
	lexer_clear(&scanner->lexer);
	scanner->source = cmd_string->data;
	scanner->mode = SCAN_MODE_STRING;
}

